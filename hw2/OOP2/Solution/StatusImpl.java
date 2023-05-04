package OOP2.Solution;

import OOP2.Provided.Status;
import OOP2.Provided.Person;

import java.util.HashSet;

public class StatusImpl implements Status {

	private final Person _publisher;
	private final Integer _id;
	private final String _content;
	private HashSet<Person> _likeSet = new HashSet<Person>();
	/*
	 * A constructor that receives the status publisher, the text of the status
	 *  and the id of the status.
	 */
	public StatusImpl(Person publisher, String content, Integer id)
	{
		_publisher = publisher;
		_content = content;
		_id = id;
	}

	@Override
	public Person getPublisher()
	{
		return _publisher;
	}

	@Override
	public Integer getId() {
		return _id;
	}

	@Override
	public String getContent()
	{
		return _content;
	}

	// no check for duplicate value because in hash set duplicate values are being ignored
	@Override
	public void like(Person p)
	{
		if(p == null)
		{
			return;
		}
		_likeSet.add(p);
	}

	@Override
	public void unlike(Person p)
	{
		if(p == null || !_likeSet.contains(p))
		{
			return;
		}
		_likeSet.remove(p);
	}

	@Override
	public Integer getLikesCount()
	{
		return _likeSet.size();
	}

	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof  Status))
		{
			return false;
		}
		Status statusToCompare = (Status) o;
		return (_publisher.equals(statusToCompare.getPublisher()) && _id.equals(statusToCompare.getId()));
	}

	@Override
	public int hashCode() {
		return _id;
	}
}