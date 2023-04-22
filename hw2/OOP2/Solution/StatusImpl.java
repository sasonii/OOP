package OOP2.Solution;

import OOP2.Provided.Status;

import OOP2.Provided.Status;
import OOP2.Provided.Person;
import java.util.Objects;
import java.util.HashSet;

public class StatusImpl implements Status {

	private Person _publisher;
	private Integer _id;
	private String _content;
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

	@java.lang.Override
	public Person getPublisher()
	{
		return _publisher;
	}

	@java.lang.Override
	public Integer getId() {
		return _id;
	}

	@java.lang.Override
	public String getContent()
	{
		return _content;
	}

	// no check for duplicate value because in hash set duplicate values are being ignored
	@java.lang.Override
	public void like(Person p)
	{
		if(p == null)
		{
			return;
		}
		_likeSet.add(p);
	}

	@java.lang.Override
	public void unlike(Person p)
	{
		if(p == null || !_likeSet.contains(p))
		{
			return;
		}
		_likeSet.remove(p);
	}

	@java.lang.Override
	public Integer getLikesCount()
	{
		return _likeSet.size();
	}

	@java.lang.Override
	public boolean equals(Object o)
	{
		if (!(o instanceof  Status))
		{
			return false;
		}
		Status status2compare = (Status) o;
		return (_publisher.equals(status2compare.getPublisher()) && _id.equals(status2compare.getId()));
	}
}

