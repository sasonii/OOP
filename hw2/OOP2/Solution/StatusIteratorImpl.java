package OOP2.Solution;
import java.util.*;
import OOP2.Provided.StatusIterator;
import OOP2.Provided.Status;
public class StatusIteratorImpl  implements StatusIterator {
    private List<Iterator<Status>> iterableList;
    private Iterator<Status> currentIterator;

    public StatusIteratorImpl(List<Iterable<Status>> iterableList) {
        this.iterableList = new ArrayList<>();
        for (Iterable<Status> iterable : iterableList) {
            this.iterableList.add(iterable.iterator());
        }
        this.currentIterator = getNextIterator();
    }

    @Override
    public boolean hasNext() {
        return currentIterator != null;
    }

    @Override
    public Status next() {
        if (!hasNext()) {
            throw new NoSuchElementException("No more elements in the list");
        }
        Status next = currentIterator.next();
        if (!currentIterator.hasNext()) {
            currentIterator = getNextIterator();
        }
        return next;
    }

    private Iterator<Status> getNextIterator() {
        while (!iterableList.isEmpty()) {
            Iterator<Status> iterator = iterableList.get(0);
            if (iterator.hasNext()) {
                iterableList.remove(0);
                return iterator;
            } else {
                iterableList.remove(0);
            }
        }
        return null;
    }

    @Override
    public void remove() {
    }
}



