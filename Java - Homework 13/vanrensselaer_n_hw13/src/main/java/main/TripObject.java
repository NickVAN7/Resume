package main;

import com.fasterxml.jackson.annotation.JsonProperty;

public class TripObject {
	private String date;
	private String hikeName;
	private String duration;
	private String attending;
	private String message;
	
	public TripObject() {
		super();
	}
	
	@JsonProperty("date")
	public String getDate() {
		return date;
	}

	public void setDate(String date) {
		this.date = date;
	}
	
	@JsonProperty("hikeName")
	public String getHikeName() {
		return hikeName;
	}
	
	public void setHikeName(String hke) {
		this.hikeName = hke;
	}
	
//	@JsonProperty("hikeName")
//	public String getHike() {
//		return hikeName;
//	}
//
//	public void setHike(String hike) {
//		this.hikeName = hike;
//	}

	@JsonProperty("duration")
	public String getDuration() {
		return duration;
	}

	public void setDuration(String duration) {
		this.duration = duration;
	}

	@JsonProperty("attending")
	public String getAttending() {
		return attending;
	}

	public void setAttending(String attending) {
		this.attending = attending;
	}
	
	@JsonProperty("message")
	public String getMessage() {
		return message;
	}
	
	public void setMessage(String message) {
		this.message = message;
	}
	

	@Override
	public String toString() {
		return "TripObject [date=" + date + ", hike=" + hikeName + ", duration=" + duration + ", attending=" + attending
				+ "]";
	}
	
	
	
	
}
