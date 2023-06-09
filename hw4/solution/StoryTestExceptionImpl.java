package solution;
import provided.StoryTestException;
import java.lang.String;

public class StoryTestExceptionImpl extends StoryTestException {
    private String sentence;
    private String storyExpected;
    private String testResult;
    private int numOfFailed;

    public StoryTestExceptionImpl(String sentence, String storyExpected, String testResult) {
        super();
        this.sentence = sentence;
        this.storyExpected = storyExpected;
        this.testResult = testResult;
        this.numOfFailed = 1;
    }

    public void increaseNumOfFails(){
        numOfFailed += 1;
    }
    public String getSentance() {
        return this.sentence;
    }

    public String getStoryExpected(){
        return this.storyExpected;
    }

    public String getTestResult(){
        return this.testResult;
    }

    public int getNumFail(){
        return this.numOfFailed;
    }
}
