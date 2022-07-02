# class-grade-calculator

This is a program to calculate final grades in my CSE 232 class from raw assignment scores.

Functions:


- The function, `GetPointTotalForStudent`, returns an int representing the number of points earned in total on a particular type of assignment. As parameters it takes a map of strings to strings (which I will call student_info) and a second parameter of a string. The map’s keys are the names of assignments and the values are the scores earned on each assignment. The map also contains other data that isn’t relevant to this function. The second parameter is a string specifying the category of assignment.

	For example, if the category is “Exam”. All the scores of assignments with “Exam” in the name should be tallied.


- The function, `GetTopNHomeworkTotalForStudent`, takes 2 parameters, the first being the same map named student_info as in the previous function. The second parameter is an int representing the number of homework assignments to tally up.
- The function, `GetNumberOfMissingLabsForStudent`, takes only student_info, and it returns the number of labs that don’t have a score of exactly “1”.
- The function, `GetPointTotalForStudent`, takes only student_info, and returns the number of points earned by that student.
- The function, `GetIDToInfoFromCSV`, takes a single parameter a string denoting a filename for a CSV formatted file. This function returns a map of string (the ID) to student_info (as mentioned previously a map of names to values/scores). This return value will be called id_to_student_info henceforth.
- The function, `GetIDToGrade`, takes a id_to_student_info map and returns a map of string (ID) to double (the student’s calculated grade). Be sure to account for the missed lab penalty.
- The function, `GetStudentsEligibleForHonorsCredit`, takes a id_to_student_info map and an int (the minimum required grade on the Project Honors) and returns a set of strings (IDs) of the students that meet the honors requirements.
