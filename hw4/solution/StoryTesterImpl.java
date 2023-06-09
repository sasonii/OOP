package solution;
import org.junit.Assert;
import org.junit.ComparisonFailure;
import provided.*;

import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Field;
import java.lang.reflect.Constructor;


public class StoryTesterImpl implements StoryTester{

    public static Object backup(Object obj) throws IllegalAccessException, InstantiationException, CloneNotSupportedException {
            Class<?> clazz = obj.getClass();
            Object backupObj = clazz.newInstance();

            Field[] fields = clazz.getDeclaredFields();
            for (Field field : fields) {
                field.setAccessible(true);

                Object fieldValue = field.get(obj);
                if (fieldValue == null) {
                    field.set(backupObj, null);
                    continue;
                }

                if (fieldValue instanceof Cloneable) {
                    try {
                        Method cloneMethod = fieldValue.getClass().getMethod("clone");
                        Object clonedValue = cloneMethod.invoke(fieldValue);
                        field.set(backupObj, clonedValue);
                        continue;
                    } catch (NoSuchMethodException | InvocationTargetException e) {
                        // Handle the exception or log the error message
                        e.printStackTrace();
                    }
                }

                Constructor<?> copyConstructor = null;
                try {
                    copyConstructor = fieldValue.getClass().getConstructor(fieldValue.getClass());
                    Object copiedValue = copyConstructor.newInstance(fieldValue);
                    field.set(backupObj, copiedValue);
                    continue;
                } catch (NoSuchMethodException | InvocationTargetException e) {
                    // Handle the exception or log the error message
                    e.printStackTrace();
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
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }

        Class<?> classTest = testClass.getClass(); // redundant?
        Object testObject = testClass.newInstance();

        // Split the string into an array of lines
        String[] lines = story.split("\n");

        String[] firstLineWords = lines[0].split("\\s+", 2);
        Method m = getMethodWithGivenAnnotationAndString(testClass, Given.class, firstLineWords[1]);
        if(m == null){
            throw new GivenNotFoundException();
        }

        String paramType = m.getParameterTypes()[0].getName();
        if(paramType.equals("java.lang.Integer")){
            m.invoke(testObject, createIntegerFromLastWord(firstLineWords[1]));
        } else {
            m.invoke(testObject, getLastWord(firstLineWords[1]));
        }

        Object testBackup = backup(testObject);

        StoryTestExceptionImpl storyTestException = null;

        // Iterate through each When, Then
        for (int i = 1; i < lines.length; i += 2) {
            testObject = (testBackup);
            testBackup = backup(testObject);

            String[] whenWords = lines[i].split("\\s+", 2);
            m = getMethodWithGivenAnnotationAndString(testClass, When.class, whenWords[1]);
            if(m == null){
                throw new WhenNotFoundException();
            }
            String[] thenWords = lines[i+1].split("\\s+", 2);
            paramType = m.getParameterTypes()[0].getName();
            if(paramType.equals("java.lang.Integer")){
                m.invoke(testObject, createIntegerFromLastWord(whenWords[1]));
            } else {
                m.invoke(testObject, getLastWord(whenWords[1]));
            }

            m = getMethodWithGivenAnnotationAndString(testClass, Then.class, thenWords[1]);
            if(m == null){
                throw new ThenNotFoundException();
            }
            paramType = m.getParameterTypes()[0].getName();
            try {
                if (paramType.equals("java.lang.Integer")) {
                    m.invoke(testObject, createIntegerFromLastWord(thenWords[1]));
                } else {
                    m.invoke(testObject, getLastWord(thenWords[1]));
                }
            } catch (InvocationTargetException e) {
                Throwable cause = e.getCause();
                if (cause instanceof ComparisonFailure) {
                    ComparisonFailure assertionError = (ComparisonFailure) cause;
                    if(storyTestException == null){
                        storyTestException = new StoryTestExceptionImpl(thenWords[1],assertionError.getExpected(), assertionError.getActual());

                    } else {
                        storyTestException.increaseNumOfFails();
                    }
                } else {
                    throw e;
                }

            }
        }

        if(storyTestException != null){
            throw storyTestException;
        }
    }

    public void testOnNestedClasses(String story, Class<?> testClass){
        if(story == null || testClass == null){
            throw new IllegalArgumentException();
        }
    }
}
