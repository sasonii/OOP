package OOP2.Solution;

import OOP2.Provided.*;
import OOP2.Solution.StatusIteratorImpl;

import java.util.*;

public class FaceOOPImpl implements FaceOOP {

	private static class Graph {
		private Map<Person, List<Person>> adjacencyList;

		public Graph() {
			adjacencyList = new HashMap<>();
		}

		public void addVertex(Person person) {
			adjacencyList.put(person, new LinkedList<>());
		}

		public void addEdge(Person source, Person destination) {
			adjacencyList.get(source).add(destination);
			adjacencyList.get(destination).add(source);
		}

		public int bfs(Person start, Person end) {
			Queue<Person> queue = new LinkedList<>();

			// Mark the start vertex as visited and enqueue it
			Map<Person, Boolean> visited = new HashMap<>();
			visited.put(start, true);
			queue.offer(start);

			// Map to keep track of the distance from the start vertex to each visited vertex
			Map<Person, Integer> distance = new HashMap<>();
			distance.put(start, 0);

			while (!queue.isEmpty()) {
				Person current = queue.poll();

				// Stop if we've reached the end vertex
				if (current.equals(end)) {
					return distance.get(current);
				}

				// Enqueue all adjacent vertices that have not been visited
				for (Person neighbor : adjacencyList.get(current)) {
					if (!visited.containsKey(neighbor)) {
						visited.put(neighbor, true);
						distance.put(neighbor, distance.get(current) + 1);
						queue.offer(neighbor);
					}
				}
			}

			// If we get here, there is no path from the start vertex to the end vertex
			return -1;
		}

		public List<Person> getFriends(Person person) {
			return adjacencyList.get(person);
		}
	}


	private Graph m_graph;
	private LinkedList<Person> m_persons;

	/**
	 * Constructor - receives no parameters and initializes the system.
	 */

	public FaceOOPImpl()
	{
		m_graph = new Graph();
		m_persons = new LinkedList<Person>();
	}

	public Person joinFaceOOP(Integer id, String name) throws PersonAlreadyInSystemException {
		if(m_persons.stream().anyMatch(obj -> obj.getId().equals(id))){
			throw new PersonAlreadyInSystemException();
		}
		Person newPerson = new PersonImpl(id, name);
		m_graph.addVertex(newPerson);
		m_persons.add(newPerson);
		return newPerson;
	}

	@Override
	public int size(){
		return m_persons.size();
	}

	@Override
	public Person getUser(Integer id) throws PersonNotInSystemException {
		Optional<Person> p = m_persons.stream().filter(obj -> obj.getId().equals(id)).findFirst();
		if(p.isPresent()){
			return p.get();
		}
		else {
			throw new PersonNotInSystemException();
		}
	}

	@Override
	public void addFriendship(Person p1, Person p2)
			throws PersonNotInSystemException, SamePersonException, ConnectionAlreadyExistException {
		if(!m_persons.contains(p1) || !m_persons.contains(p1)){
			throw new PersonNotInSystemException();
		}
		if(p1.equals(p2)){
			throw new SamePersonException();
		}
		if(m_graph.getFriends(p1).contains(p2)){
			throw new ConnectionAlreadyExistException();
		}
		m_graph.addEdge(p1, p2);
	}

	@Override
	public StatusIterator getFeedByRecent(Person p)
			throws PersonNotInSystemException
	{
		if(!m_persons.contains(p)){
			throw new PersonNotInSystemException();
		}
		List<Person> friendsList = m_graph.getFriends(p);
		Collections.sort(friendsList);
		List<Iterable<Status>> listOfIterables = new ArrayList<>();
		for (Person friend : friendsList) {
			listOfIterables.add(friend.getStatusesRecent());
		}
		StatusIterator it = new StatusIteratorImpl(listOfIterables);
		return it;

	}

	@Override
	public StatusIterator getFeedByPopular(Person p)
			throws PersonNotInSystemException
	{
		if(!m_persons.contains(p)){
			throw new PersonNotInSystemException();
		}
		List<Person> friendsList = m_graph.getFriends(p);
		Collections.sort(friendsList);
		List<Iterable<Status>> listOfIterables = new ArrayList<>();
		for (Person friend : friendsList) {
			listOfIterables.add(friend.getStatusesPopular());
		}
		StatusIterator it = new StatusIteratorImpl(listOfIterables);
		return it;
	}

	@Override
	public Integer rank(Person source, Person target)
			throws PersonNotInSystemException, ConnectionDoesNotExistException
	{
		if(!m_persons.contains(source) || !m_persons.contains(target)){
			throw new PersonNotInSystemException();
		}
		int res = m_graph.bfs(source, target);
		if(res == -1){
			throw new ConnectionDoesNotExistException();
		}
		return res;
	}

	@Override
	public Iterator<Person> iterator() {
		return m_persons.iterator();
	}
}
