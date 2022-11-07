package main;

import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("example")
public class Endpoints {

	@POST
	@Path("/loadJson")
	@Produces(MediaType.APPLICATION_JSON)
	public TripObject getTrip(TripObject t) {
		TripObject trip = new TripObject();
		trip.setDate(t.getDate());
		trip.setHikeName(t.getHikeName());
		trip.setDuration(t.getDuration());
		trip.setAttending(t.getAttending());
		
		System.out.println("getDate is " + t.getDate() 
						+ "\ngetHikeName is " + t.getHikeName() 
						+ "\ngetDuration is " + t.getDuration() 
						+ "\ngetAttending is " + t.getAttending());
		
		
		Validate val = new Validate(t.getDate(), t.getHikeName(), t.getDuration(), t.getAttending());
		
		trip.setMessage(val.message);
		t.setMessage(val.message);
		
		Response.ok().tag(t.toString()).build();
		
		System.out.println(trip);
		return trip;
	}
}
