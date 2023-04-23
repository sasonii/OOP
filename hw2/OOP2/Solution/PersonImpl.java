package OOP2.Solution;

import OOP2.Provided.ConnectionAlreadyExistException;
import OOP2.Provided.Person;
import OOP2.Provided.SamePersonException;
import OOP2.Provided.Status;

import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;
import java.util.LinkedList;


public class PersonImpl implements Person {

	private final String m_name;
	private final Integer m_id;
	private LinkedList<Status> m_statuses;
	private Integer m_numberOfStatuses;

	private HashSet<Person> m_friends_set;

	/**
	 * Constructor receiving person's id and name.
	 */
	public PersonImpl(Integer id, String name) {
		m_id = id;
		m_name = name;
		m_statuses = new LinkedList<Status>();
		m_numberOfStatuses = 0;
		m_friends_set = new HashSet<Person>();
	}

	@Override
	public Integer getId() {
		return m_id;
	}

	@Override
	public String getName() {
		return m_name;
	}

	@Override
	public Status postStatus(String content) {
		if(content == null){
			return null;
		}
		StatusImpl newStatus = new StatusImpl(this, content, m_numberOfStatuses);
		m_numberOfStatuses += 1;
		m_statuses.add(newStatus);
		return newStatus;
	}

	@Override
	public void addFriend(Person p) throws SamePersonException, ConnectionAlreadyExistException {
		if(p == this){
			throw new SamePersonException();
		}
		if(m_friends_set.contains(p)){
			throw new ConnectionAlreadyExistException();
		}
		m_friends_set.add(p);
	}

	@Override
	public Collection<Person> getFriends(){
		return m_friends_set;
	}

	@Override
	public Iterable<Status> getStatusesRecent() {
		m_statuses.sort((o1, o2) -> o2.getId() - o1.getId());
		return m_statuses;
	}

	@Override
	public Iterable<Status> getStatusesPopular() {
		m_statuses.sort((o1, o2) -> {
			if (o1.getLikesCount() != o2.getLikesCount()) {
				return o2.getLikesCount() - o1.getLikesCount();
			}
			return o2.getId() - o1.getId();
		});
		return m_statuses;
	}

	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof  Person))
		{
			return false;
		}
		Person personToCompare = (Person) o;
		return m_id.equals(personToCompare.getId());
	}

	@Override
	public int compareTo(Person p) {
		if(this.m_id > p.getId())
			return 1;
		else if (this.m_id < p.getId())
			return -1;
		else
			return 0;
	}
}
