package solution;
import org.junit.Assert;
import org.junit.ComparisonFailure;
import provided.*;

import java.lang.reflect.Constructor;
import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Field;
import java.lang.reflect.Constructor;

import java.util.ArrayList;
import java.util.List;


public class StoryTesterImpl implements StoryTester{
    private static Field[] getAllDeclaredFields(Class<?> currentClass) {

        Field[] fields = currentClass.getDeclaredFields();

        // If the current class has a superclass, recursively get its fields too
        Class<?> superClass = currentClass.getSuperclass();
        if (superClass != null && !superClass.getName().equals("java.lang.Object")) {
            Field[] superFields = getAllDeclaredFields(superClass);
            Field[] allFields = new Field[fields.length + superFields.length];
            System.arraycopy(fields, 0, allFields, 0, fields.length);
            System.arraycopy(superFields, 0, allFields, fields.length, superFields.length);
            fields = allFields;
        }

        return fields;
    }
    public static Object backup(Object obj, Class<?> testClass, boolean isInner, List<Class<?>> classes) throws IllegalAccessException, InstantiationException, CloneNotSupportedException, InvocationTargetException {
            Class<?> clazz = obj.getClass();
            Constructor<?> initialConstructor = testClass.getDeclaredConstructors()[0];
            initialConstructor.setAccessible(true);
            Object backupObj = initialConstructor.newInstance();
            if(isInner){
                for (int i = classes.size() - 2; i >= 0; i--) {
                    Class<?> innerClass = classes.get(i);
                    initialConstructor = innerClass.getDeclaredConstructors()[0];
                    initialConstructor.setAccessible(true);
                    backupObj = initialConstructor.newInstance(backupObj);
                }
//                constructor = clazz.getDeclaredConstructors()[0];
//                constructor.setAccessible(true);
//                backupObj = constructor.newInstance(backupObj);
                // maybe there is no need to this
//                testObject = testClass.getDeclaredConstructors()[0].newInstance();
//                testObject = innerTestClass.getDeclaredConstructors()[0].newInstance(testObject);
            }

            Field[] fields = getAllDeclaredFields(clazz);
            for (Field field : fields) {
                field.setAccessible(true);

                Object fieldValue = field.get(obj);
                if (fieldValue == null) {
                    field.set(backupObj, null);
                    continue;
                }

                if (fieldValue instanceof Cloneable) {
                    try {
                        // Get all methods of the current class
                        Method[] methods = fieldValue.getClass().getDeclaredMethods();
                        boolean found = false;
                        // Iterate through the methods
                        for (Method method : methods) {
                            // Check if the method has the Given annotation
//                            System.out.println(method.getName());
                            if(method.getName().equals("clone")) {
                                method.setAccessible(true);
                                Object clonedValue = method.invoke(fieldValue);
                                field.set(backupObj, clonedValue);
                                found = true;
                                break;
                            }
                        }
                        if(found){
                            continue;
                        }

                    } catch (InvocationTargetException e) {
                        // Handle the exception or log the error message
                        //e.printStackTrace();
                    }
                }

                Constructor<?> copyConstructor = null;
                try {
                    boolean found = false;
                    Constructor<?>[] constructors = clazz.getDeclaredConstructors();
                    for (Constructor<?> constructor : constructors) {
                        Class<?>[] parameterTypes = constructor.getParameterTypes();
//                        if(parameterTypes.length == 0){
//                            constructor.setAccessible(true);
//                            Object copiedValue = constructor.newInstance();
//                            field.set(backupObj, copiedValue);
//                            break;
//                        }
                        if (parameterTypes.length == 1 && parameterTypes[0].equals(fieldValue.getClass())) {
                            // Found the desired constructor
                            constructor.setAccessible(true);
                            Object copiedValue = constructor.newInstance(fieldValue);
                            field.set(backupObj, copiedValue);
                            found = true;
                            break;
                        }
                    }
//                    copyConstructor = fieldValue.getClass().getConstructor(fieldValue.getClass());
                    if(found){
                        continue;
                    }
                } catch (InvocationTargetException e) {
                    // Handle the exception or log the error message
                    //e.printStackTrace();
                } catch (IllegalArgumentException e2){

                }

                field.set(backupObj,  fieldValue);
            }

            return backupObj;
        }

    private static Method getMethodWithGivenAnnotationAndString(Class<?> testClass, Class<? extends Annotation> annotationClass, String searchString) {
        Class<?> currentClass = testClass;

        // Iterate through the class hierarchy
        while (currentClass != null) {
            // Get all methods of the current class
            Method[] methods = currentClass.getDeclaredMethods();

            // Iterate through the methods
            for (Method method : methods) {
                // Check if the method has the Given annotation
                Annotation givenAnnotation = method.getAnnotation(annotationClass);
                if (givenAnnotation != null && areStringsEqualExceptLastWord(getAnnotationValue(givenAnnotation),searchString)){
                    method.setAccessible(true);
                    return method; // Found a method with the Given annotation and matching string
                }
            }

            // Move to the superclass for the next iteration
            currentClass = currentClass.getSuperclass();
        }

        return null; // No method with Given annotation found
    }
    private static boolean areStringsEqualExceptLastWord(String str1, String str2) {
        String[] words1 = str1.split(" ");
        String[] words2 = str2.split(" ");

        // Check if the number of words is the same
        if (words1.length != words2.length) {
            return false;
        }

        // Iterate over the words, except for the last word
        for (int i = 0; i < words1.length - 1; i++) {
            if (!words1[i].equals(words2[i])) {
                return false; // Words are not equal
            }
        }

        return true; // All words are equal except the last one
    }
    private static String getAnnotationValue(Annotation annotation) {
        if (annotation instanceof Given) {
            Given givenAnnotation = (Given) annotation;
            return givenAnnotation.value();
        }

        if (annotation instanceof Then) {
            Then givenAnnotation = (Then) annotation;
            return givenAnnotation.value();
        }

        if (annotation instanceof When) {
            When givenAnnotation = (When) annotation;
            return givenAnnotation.value();
        }

        return ""; // Default value if the annotation does not have a "value" parameter
    }
    private static String getLastWord(String str) {
        String[] words = str.split(" ");
        if (words.length > 0) {
            return words[words.length - 1];
        }
        return null;
    }
    private static Integer createIntegerFromLastWord(String str) {
        // Split the string into words
        String[] words = str.split(" ");

        // Check if there is at least one word
        if (words.length > 0) {
            // Get the last word
            String lastWord = words[words.length - 1];

            try {
                // Try parsing the last word as an integer

                // Create a new Integer object with the parsed value
                return Integer.parseInt(lastWord);
            } catch (NumberFormatException e) {
                // The last word is not a valid integer
                // Handle the exception or return null/throw an error as needed
                Assert.assertTrue(false);
            }
        }

        // The string does not have a last word or the last word is not an integer
        // Handle the case or return null/throw an error as needed
        return null;
    }
    public void testOnInheritanceTree(String story, Class<?> testClass) throws IllegalArgumentException, WordNotFoundException, InstantiationException, IllegalAccessException, InvocationTargetException, CloneNotSupportedException, StoryTestExceptionImpl {
        runTest(story, testClass, false, null);
    }
    private static Method getMethodFromNestedClassWithGivenAnnotationAndString(Class<?> testClass, Class<? extends Annotation> annotationClass, String searchString) {
        Method m = getMethodWithGivenAnnotationAndString(testClass, annotationClass, searchString);
        if(m != null) {
            return m;
        }
        for (Class<?> nestedClass : testClass.getDeclaredClasses()) {
            m = getMethodFromNestedClassWithGivenAnnotationAndString(nestedClass, annotationClass, searchString);
            if(m != null){
                return m;
            }
        }
        return null;
    }
    private static Method getMethod(Class<?> testClass, Class<? extends Annotation> annotationClass, String searchString, boolean isNested){
        if(isNested) {
            return getMethodFromNestedClassWithGivenAnnotationAndString(testClass, annotationClass, searchString);
        }
        return getMethodWithGivenAnnotationAndString(testClass, annotationClass, searchString);
    }


    private static void runTest(String story, Class<?> testClass, boolean isNested, List<Class<?>> classes) throws IllegalArgumentException, WordNotFoundException, InstantiationException, IllegalAccessException, InvocationTargetException, CloneNotSupportedException, StoryTestExceptionImpl {
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }
        Object testObject;
        if(isNested){
            Class<?> clazz = classes.get(classes.size() - 1);
            Constructor<?> constructor = clazz.getDeclaredConstructors()[0];
            constructor.setAccessible(true);
            testObject = constructor.newInstance();

            for (int i = classes.size() - 2; i >= 0; i--) {
                Class<?> innerClass = classes.get(i);
                constructor = innerClass.getDeclaredConstructors()[0];
                constructor.setAccessible(true);
                testObject = constructor.newInstance(testObject);
            }
        }
        else {
            Constructor<?> constructor = testClass.getDeclaredConstructors()[0];
            constructor.setAccessible(true);
            testObject = constructor.newInstance();
        }

        // Split the string into an array of lines
        String[] lines = story.split("\n");

        String[] firstLineWords = lines[0].split("\\s+", 2);
        Method m = getMethod(testClass, Given.class, firstLineWords[1], isNested);
        if(m == null){
            throw new GivenNotFoundException();
        }

        String paramType = m.getParameterTypes()[0].getName();
        if(paramType.equals("java.lang.Integer") || paramType.equals("int")){
            m.invoke(testObject, createIntegerFromLastWord(firstLineWords[1]));
        } else {
            m.invoke(testObject, getLastWord(firstLineWords[1]));
        }

        Object testBackup = backup(testObject, testClass, isNested, classes);

        StoryTestExceptionImpl storyTestException = null;

        // Iterate through each When, Then
        for (int i = 1; i < lines.length; i++) {
            String[] sentenceWords = lines[i].split("\\s+", 2);
            if(sentenceWords[0].equals("When")) {
                testObject = (testBackup);
                testBackup = backup(testObject, testClass, isNested, classes);
                String[] whenWords = sentenceWords;
                m = getMethod(testClass, When.class, whenWords[1], isNested);
                if (m == null) {
                    throw new WhenNotFoundException();
                }
                paramType = m.getParameterTypes()[0].getName();
                if (paramType.equals("java.lang.Integer") || paramType.equals("int")) {
                    m.invoke(testObject, createIntegerFromLastWord(whenWords[1]));
                } else {
                    m.invoke(testObject, getLastWord(whenWords[1]));
                }
            } else {
                String[] thenWords = sentenceWords;
                m = getMethod(testClass, Then.class, thenWords[1], isNested);
                if (m == null) {
                    throw new ThenNotFoundException();
                }
                paramType = m.getParameterTypes()[0].getName();
                try {
                    if (paramType.equals("java.lang.Integer") || paramType.equals("int")) {
                        m.invoke(testObject, createIntegerFromLastWord(thenWords[1]));
                    } else {
                        m.invoke(testObject, getLastWord(thenWords[1]));
                    }
                } catch (InvocationTargetException e) {
                    Throwable cause = e.getCause();
                    if (cause instanceof ComparisonFailure) {
                        ComparisonFailure assertionError = (ComparisonFailure) cause;
                        if (storyTestException == null) {
                            storyTestException = new StoryTestExceptionImpl(lines[i], assertionError.getExpected(), assertionError.getActual());

                        } else {
                            storyTestException.increaseNumOfFails();
                        }
                    } else {
                        throw e;
                    }
                }
            }
        }

        if(storyTestException != null){
            throw storyTestException;
        }
    }
    public void testOnNestedClasses(String story, Class<?> testClass) throws WordNotFoundException, InvocationTargetException, StoryTestExceptionImpl, InstantiationException, IllegalAccessException, CloneNotSupportedException {
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }
        // Split the string into an array of lines
        String[] lines = story.split("\n");

        String[] firstLineWords = lines[0].split("\\s+", 2);

        List<Class<?>> classes = new ArrayList<>();
        Class<?> innerTestClass = findNestedClassWithGivenAnnotationAndString(testClass, Given.class, firstLineWords[1], classes);
        if(innerTestClass == null){
            throw new GivenNotFoundException();
        }
        runTest(story, testClass, true, classes);
    }
//    private static List<Class<?>> findNestedClassesWithGivenAnnotationAndString(
//            Class<?> testClass, Class<? extends Annotation> annotationClass, String searchString) {
//        List<Class<?>> classes = new ArrayList<>();
//        findNestedClassesWithGivenAnnotationAndString(testClass, annotationClass, searchString, classes);
//        return classes;
//    }
    private static Class<?> findNestedClassWithGivenAnnotationAndString(Class<?> testClass, Class<? extends Annotation> annotationClass, String searchString,List<Class<?>> classes) {
        Method m = getMethodWithGivenAnnotationAndString(testClass, annotationClass, searchString);
        if(m != null) {
            classes.add(testClass);
            return testClass;
        }
        for (Class<?> nestedClass : testClass.getDeclaredClasses()) {
            Class<?> returnClass = findNestedClassWithGivenAnnotationAndString(nestedClass, annotationClass, searchString, classes);
            if(returnClass != null){
                classes.add(testClass);
                return returnClass;
            }
        }
        return null;
    }
}
