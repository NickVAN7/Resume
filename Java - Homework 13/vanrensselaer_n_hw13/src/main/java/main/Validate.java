package main;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonIgnore;
import bookingrate.BookingDay;
import bookingrate.Rates;
//import main.Dates; 

// This bean will be used to valid the data from the index.html form
public class Validate {
	// Setting date variables
	int startDay = -1;
	int startMonth = -1;
	int startYear = -1;

	String date = "";
	String hikeName = "";
	String hikeOut = "";
	int duration = -1;
	int attending = -1;

	// Placeholder for valid durations
	private int validDur[] = null;

	private int datePieces[] = null;

	// Initializing temp and bean variables
	double cost = -1.0;
	double cst = -1.0;
	String message = null;
	String msg = null;

	static Rates rate;

	// Valid variable
	public boolean valid = false;

	// Default constructor
	public Validate() {
	}

	public Validate(String dte, String hikeName, String dur, String att) {
		
		// Testing if hikeName is empty...
		// If so, gives error message
		if (hikeName.isEmpty()) {
			msg = "There has been an Error! Please select a hike location. ";
			System.out.println("Input is Invalid - No location");
		} else {
			// Testing if the dur is empty,
			// If so, gives Error message
			if (dur.isEmpty()) {
				msg = "There has been an Error! Please select a hike duration. ";
				System.out.println("Input is Invalid - No duration");
			} else {

				// Testing if the attending number of people is null, if it isn't the testing
				// continues
				if (!att.isEmpty()) {

					try {
						// Added splitDate method this class instead of outside of it

						// Splitting date into Day/Month/Year pieces
						date = dte;
						datePieces = splitDate(dte);
						startYear = datePieces[2];
						startMonth = datePieces[0];
						startDay = datePieces[1];

						// Setting dur variable based on duration input
						duration = Integer.parseInt(dur);
						// Setting att variable based on attending input
						attending = Integer.parseInt(att);

						System.out.println("Duration is: " + duration);
						System.out.println("Number attending is: " + attending);

						// Creating a new instance of BookingDay using the day values
						BookingDay newDay = new BookingDay(startYear, startMonth, startDay);

						// Switch statement to select correct Hike rates and valid durations
						// Cloning the rate.validDurations array into a local array to print out valid
						// dates
						switch (hikeName) {
						case "GARDINER":
							rate = new Rates(Rates.HIKE.GARDINER);
							validDur = rate.validDurations.clone();
							hikeOut = "Gardiner Lake Hike";
							break;
						case "HELLROARING":
							rate = new Rates(Rates.HIKE.HELLROARING);
							validDur = rate.validDurations.clone();
							hikeOut = "Hellroaring Plateau Hike";
							break;
						case "BEATEN":
							rate = new Rates(Rates.HIKE.BEATEN);
							validDur = rate.validDurations.clone();
							hikeOut = "Beaten Path Hike";
							break;
						default:
							break;
						}

						System.out.println("Hike is: " + hikeName + "\nHike Output is: " + hikeOut);

						// Testing for a valid date
						if (newDay.isValidDate()) {
							rate.setBeginDate(newDay);

							// Testing for a valid trip duration for the selected hike
							if (rate.setDuration(duration)) {

								// Testing for valid trip start dates - in/out of season
								if (rate.isValidDates()) {

									if (attending < 1 || attending > 10) {
										msg = "There has been an Error! The number of people attending must be between 1 and 10."
												+ "<br>" + "You selected: " + att;
										System.out.println("Input is Invalid - Bad attending");
									} else {
										cst = rate.getCost();
										cst = cst * attending;

										valid = true;
										System.out.println("Input is Valid");
									}
								}
								// Error message for invalid start dates
								else {
									msg = "There has been an Error! You cannot choose that tour date. "
											+ "<br>" + newDay.toString() + " is outside of our Tour season. ";
									System.out.println("Input is Invalid - Date Outside of season");
								}
							}
							// Error message for invalid trip durations
							// Prints out the valid duration options
							else {
								msg = "There has been an Error! That duration (" + dur
										+ " day(s)) cannot be selected for that trip (" + hikeOut + ").";
								msg +=  "<br>" + "The valid durations for the " + hikeOut + " are: ";
								for (int i = 0; i < validDur.length; i++) {
									msg += validDur[i] + " days  ";
								}
								System.out.println("Input is Invalid - Invalid duration");
							}
						}
						// Error message for invalid dates
						else {
							msg = "There has been an Error! The date you selected " + newDay.toString()
									+ " is not a valid date. ";
							System.out.println("Input is Invalid - Bad date");
						}
					}
					// Catch statement for parsing errors
					catch (Exception e) {
						msg = "There has been an Error! The input was invalid. ";
						System.out.println("Input is Invalid");
					}
				}
				// Error message if the attending input is null
				else {
					msg = "There has been an Error! The Number of attending people was not submitted. Please try again!";
					System.out.println("Input is Invalid - No attending");
				}
			}
		}

		// If the temp message variable is not empty (null), it returns that Error
		// message
		if (msg != null) {
			message = msg;
			System.out.println("Message is: " + message);
		}
		// If the msg variable is empty, there were no errors. - so it returns the cost
		// message
		else {
			message = " Your total trip cost is: " + String.format("$%.2f", cst);
			cost = cst;
			System.out.println("Message is: " + message);
		}
	}

	// Getters and Setters for bean data
	// Don't necessarily need setters, but it doesn't hurt
	@JsonProperty("date")
	public String getDate() {
		return date;
	}

	public void setDate(String dte) {
		this.date = dte;
	}
	
	@JsonIgnore
	public String getHikeOut() {
		return hikeOut;
	}

	public void setHikeOut(String hke) {
		this.hikeOut = hke;
	}
	
	@JsonProperty("hike")
	public String getHikeName() {
		return hikeName;
	}

	public void setHikeName(String hke) {
		this.hikeName = hke;
	}

	@JsonProperty("duration")
	public int getDuration() {
		return duration;
	}

	public void setDuration(int dur) {
		this.duration = dur;
	}

	@JsonProperty("attending")
	public int getAttending() {
		return attending;
	}

	public void setAttending(int att) {
		this.attending = att;
	}

	@JsonIgnore
	public String getMessage() {
		return message;
	}

	public void setMessage(String msg) {
		this.message = msg;
	}
	
	

	@Override
	public String toString() {
		return "Validate [date=" + date + ", hikeOut=" + hikeOut + ", duration=" + duration + ", attending=" + attending
				+ ", cost=" + cost + ", message=" + message + ", valid=" + valid + "]";
	}

	private int[] splitDate(String dte) {
		String str = dte;
		String pieces[] = str.split("/");
		int out[] = new int[pieces.length];

		try {
			for (int i = 0; i < pieces.length; i++) {
				out[i] = Integer.parseInt(pieces[i]);
			}

		} catch (NumberFormatException e) {
			message = "There has been an Error! \nThe date is not in the correct format. ";

		}

		return out;
	}
	


}

