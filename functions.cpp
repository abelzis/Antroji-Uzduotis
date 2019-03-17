#include "functions.h"



//function UI
//begin of 'VECTOR declaration'
#ifdef VECTOR
	void takeInput(vector<Student>& student, vector<Student>& cool_stud, vector<Student>& lame_stud,
		ifstream& file_inp,
		durationDouble& clock_file, tmPt& clock_temp)
#endif
//end of 'VECTOR declaration'

//begin of 'LIST declaration'
#ifdef LIST
	void takeInput(list<Student>& student, list<Student>& cool_stud, list<Student>& lame_stud,
		ifstream& file_inp,
		durationDouble& clock_file, tmPt& clock_temp)
#endif
//end of 'LIST declaration'

//begin of 'DEQUE declaration'
#ifdef DEQUE
	void takeInput(deque<Student>& student, deque<Student>& cool_stud, deque<Student>& lame_stud,
		ifstream& file_inp,
		durationDouble& clock_file, tmPt& clock_temp)
#endif
//end of 'DEQUE declaration'
{
	string end_var = "-2", ifstreamName = "kursiokai.txt", ofstreamName;

	//begin of 'get student input'
	while (end_var != "end")
	{
		cin >> end_var;

		//prints instruction list
		if (end_var == "help")
		{
			instructions();
			continue;
		}

		//user can open any file if the file exists and read from it
		//begin of 'open ifstream file'
		if (end_var == "open")
		{
			while (1)
			{
				cout << "Follow the template - filename.txt. - 'exit' to leave 'open'.\n";
				cout << "Enter full file name you want to access : ";
				cin >> ifstreamName;	//get input stream text

				//if user wants to leave this section
				if (ifstreamName == "exit")
				{
					ifstreamName = "kursiokai.txt";	//set to default ifstream
					break;
				}

				//test if the user has written in form filename.txt
				string test_if_txt;
				if (ifstreamName.length() > 4)
				{
					test_if_txt.append(ifstreamName, ifstreamName.length() - 4, 4);
					if (test_if_txt == ".txt")
						break;
				}
			}

			//if the ifstreamName string is not empty
			//begin of 'write random student objects'
			if (!ifstreamName.empty())
			{
				try
				{
					//file_inp.open(ifstreamName, std::fstream::in);	//get the ofstream
					//file_inp.open(ifstreamName);	//get the ofstream
					openFile(file_inp, ifstreamName);
					if (!file_inp.is_open())
						throw "Error: can't open selected file.";

					cout << "File successfully has been opened.\n";
					continue;
				}
				catch (const char* msg)	//if error catch message
				{
					cout << "\n" << msg << "\n\n";	//print error message
					continue;
				}
			}
			openFile(file_inp);
			continue;
		}
		//end of 'open ifstream file'

		//if user wants to generate file with certain amount of students
		//begin of 'generate-file'
		if (end_var == "generate-file")
		{
			cout << "You are able to generate files with random student information. Please note, that only '.txt' extensions are supported.\n";
			while (1)
			{
				cout << "Follow the template - filename.txt. - 'exit' to leave 'generate-file'.\n";
				cout << "Enter full file name you want to create: ";
				cin >> ofstreamName;

				//if user wants to leave this section
				if (ofstreamName == "exit")
				{
					ofstreamName.clear();	//empty the string
					break;
				}

				//test if the user has written in form filename.txt
				string test_if_txt;
				if (ofstreamName.length() > 4)
				{
					test_if_txt.append(ofstreamName, ofstreamName.length() - 4, 4);
					if (test_if_txt == ".txt")
						break;
				}

			}

			//if the ofstreamName string is not empty
			//try to write randomized student objects to file named ofstreamName
			//begin of 'write random student objects'
			if (!ofstreamName.empty())
			{
				try
				{
					ofstream rand_out(ofstreamName);	//get the ofstream

					//get amount of randomized students
					cout << "Enter the number of randomized student objects to create: ";
					string get_rand_amount;
					cin >> get_rand_amount;

					bool is_number = checkIfStrIsNum(get_rand_amount);	//check if the given string is number

					//if string is only digits
					if (is_number)
					{
						try
						{
							cout << "Beginning to generate file...";
							//clock_temp = clock();	//begin time
							clock_temp = hrClock::now();

							generateFile(rand_out, std::stoi(get_rand_amount));	//generate file with student objects

							//end time
							//clock_file = clock() - clock_temp + clock_file;
							clock_file += durationDouble(hrClock::now() - clock_temp);
							//cout << "Finished! Took: " << (double)(clock() - clock_temp) / CLOCKS_PER_SEC << "s\n";
							cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
						}
						catch (const char* msg)
						{
							cout << "\n" << msg << "\n\n";	//print error message
							continue;
						}
					}


					else
						throw "Error: input is not a number.";	//throw error
					continue;
				}
				catch (const char* msg)	//if error catch message
				{
					cout << "\n" << msg << "\n\n";	//print error message
					continue;
				}
			}
			//end of 'write random student objects'
		}
		//end of 'generate-file'

		//if user wants to get input from file 'kursiokai.txt', should write 'file'
		if (end_var == "file")
		{
			cout << "Beginning to read from file...";

			clock_temp = hrClock::now();

			try
			{
				readFromFile(file_inp, student);
			}
			catch (const char* msg)	//if error catch message
			{
				cout << "\n" << msg << "\n\n";	//print error message
				continue;
			}

			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			continue;
		}


		//if user wants to write input into vector
		if (end_var == "input")
		{
			try
			{
				getInput(student);	//lets the user to write it's own input into vector array
			}
			catch (const char* msg) //if error
			{
				cout << "\n" << msg << "\n\n";	//print error message
			}
		}


		//calculate average
		if (end_var == "avg")
		{
			//begin of 'calculate average'
			cout << "Beginning to calculate averages...";
			clock_temp = hrClock::now();
			for (auto & it : student)
				it.avg_final = avgCalc(it.hw, it.egz);	//calculate average
			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			//end of 'calculate average'
			continue;
		}


		//calculate median
		if (end_var == "med")
		{
			//begin of 'calculate median'
			cout << "Beginning to calculate medians...";
			clock_temp = hrClock::now();
			for (auto & it : student)
				it.med_final = medCalc(it.hw, it.egz);	//calculate median
			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			//end of 'calculate median'
			continue;
		}



		//if 'best-worst' is selected, pick students with high marks in one array, and students with bad marks in another array
		if (end_var == "best-worst")
		{
			try
			{
				cout << "Beginning to seperate best from worst...";
				clock_temp = hrClock::now();

				sortBestWorst(student, cool_stud, lame_stud);	//sort best from worst

				//end time
				clock_file += durationDouble(hrClock::now() - clock_temp);
				cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			}
			catch (const char* msg)
			{
				cout << "\n" << msg << "\n\n";	//print error message
			}

			continue;
		}



		//if 'best-worst' is selected, pick students with high marks in one array, and students with bad marks in another array
		if (end_var == "best-worst2")
		{
			try
			{
				cout << "Beginning to seperate best from worst...";
				clock_temp = hrClock::now();

				sortBestWorst2(student, lame_stud);	//sort best from worst

				//end time
				clock_file += durationDouble(hrClock::now() - clock_temp);
				cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			}
			catch (const char* msg)
			{
				cout << "\n" << msg << "\n\n";	//print error message
			}

			continue;
		}


		//if user wants to write best-worst students into seperate files
		if (end_var == "best-worst-file")
		{
			//if vectors are empty, error and continue
			if (cool_stud.empty() && lame_stud.empty())
			{
				cout << "Error: cool and lame vectors are empty.\n";
				continue;
			}


			string ofstreamName_temp;
			while (1)
			{
				cout << "Enter a number x, to give number cool_x.txt, lame_.txt. - 'exit' to leave this section 'best-worst-file'.\n";
				cout << "Enter a number: ";

				cin >> ofstreamName_temp;	//get output stream text name

				//if user wants to leave this section
				if (ifstreamName == "exit")
				{
					ifstreamName.clear();	//empty the string
					break;
				}

				//check if input string is number
				if (checkIfStrIsNum(ofstreamName_temp))
					break;

				cout << "\nYou did not enter a number. Try again and follow the instructions.\n";	//error msg
			}
			//if given string is not empty, means its a number
			if (!ofstreamName_temp.empty())
			{
				try
				{
					cout << "Beginning to write best and worst students to files...";
					clock_temp = hrClock::now();	//begin time

					if (cool_stud.empty())
						writeToFileBestWorst(ofstreamName_temp, student, lame_stud);
					else
						writeToFileBestWorst(ofstreamName_temp, cool_stud, lame_stud);	//output results in files

					//end time
					clock_file += durationDouble(hrClock::now() - clock_temp);
					cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";

				}
				catch (const char* msg)	//if error
				{
					cout << "\n" << msg << "\n\n";	//print error message
				}
			}
			continue;
		}

		//if user wants to clear memory
		if (end_var == "del-stud")
		{
			try
			{
				//delete student object
				deleteStudentVector(student);	
				deleteStudentVector(cool_stud);
				deleteStudentVector(lame_stud);
			}
			catch (const char* msg)	//if error
			{
				cout << "\n" << msg << "\n\n";	//print error message
			}
		}

		//if user wants to end the input, write 'end' to break the loop
		if (end_var == "end")
			break;

		if (end_var == "test")
		{
			openFile(file_inp, "million.txt");

			clock_temp = hrClock::now();
			cout << "Beginning to read from file...";
			readFromFile(file_inp, student);

			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";


			//begin of 'calculate average'
			cout << "Beginning to calculate averages...";
			clock_temp = hrClock::now();
			for (auto & it : student)
				it.avg_final = avgCalc(it.hw, it.egz);	//calculate average
			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			//end of 'calculate average'


			//begin of 'calculate median'
			cout << "Beginning to calculate medians...";
			clock_temp = hrClock::now();
			for (auto & it : student)
				it.med_final = medCalc(it.hw, it.egz);	//calculate median
			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";
			//end of 'calculate median'


			cout << "Beginning to seperate best from worst...";
			clock_temp = hrClock::now();

			sortBestWorst(student, cool_stud, lame_stud);	//sort best from worst
			//sortBestWorst2(student, lame_stud);

			//end time
			clock_file += durationDouble(hrClock::now() - clock_temp);
			cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";




			//if vectors are empty, error and continue
			if (cool_stud.empty() && lame_stud.empty())
			{
				cout << "Error: cool and lame vectors are empty.\n";
				continue;
			}


			string ofstreamName_temp;
			while (1)
			{
				cout << "Enter a number x, to give number cool_x.txt, lame_.txt. - 'exit' to leave this section 'best-worst-file'.\n";
				cout << "Enter a number: ";

				cin >> ofstreamName_temp;	//get output stream text name

				//if user wants to leave this section
				if (ifstreamName == "exit")
				{
					ifstreamName.clear();	//empty the string
					break;
				}

				//check if input string is number
				if (checkIfStrIsNum(ofstreamName_temp))
					break;

				cout << "\nYou did not enter a number. Try again and follow the instructions.\n";	//error msg
			}
			//if given string is not empty, means its a number
			if (!ofstreamName_temp.empty())
			{
				try
				{
					cout << "Beginning to write best and worst students to files...";
					clock_temp = hrClock::now();	//begin time

					if (cool_stud.empty())
						writeToFileBestWorst(ofstreamName_temp, student, lame_stud);
					else
						writeToFileBestWorst(ofstreamName_temp, cool_stud, lame_stud);	//output results in files

					//end time
					clock_file += durationDouble(hrClock::now() - clock_temp);
					cout << "Finished! Took: " << durationDouble(hrClock::now() - clock_temp).count() << "s\n";

				}
				catch (const char* msg)	//if error
				{
					cout << "\n" << msg << "\n\n";	//print error message
				}
			}
			break;
		}


		//if no correct input
		cout << "\nPlease follow the instructions. Type 'help' for more information.\n";

	}
	//end of 'get student input'
}

//function prints instruction set
void instructions()
{
	cout << "Programa suskaiciuoja namu darbu bei egzamino galutinius ivertinimus.\n";
	cout << "Komandu sarasas:\n";
	cout << "\t'help' ismeta instrukciju sarasa.\n";
	cout << "\t'open' leidzia atidaryti pasirinkta faila.\n";
	cout << "\t'generate-file' leidzia sugeneruot faila su atsitiktiniais studentu duomenimis.\n";
	cout << "\t'file' nuskaito is atidaryto failo duomenis ir ikelia i konteineri.\n";
	cout << "\t'input' leidzia ranka irasyti duomenis i konteineri.\n";
	cout << "\t'avg' suskaiciuoja duomenu galutini vidurki.\n";
	cout << "\t'med' suskaiciuoja duomenu galutini mediana.\n";
	cout << "\t'best-worst' surusiuoja i atskirus konteinerius geriausius studentus nuo blogiausiu.\n";
	cout << "\t'best-worst2' atrenka blogiausius studentus ir juos sudeda i nauja konteineri, o geriausius palieka.\n";
	cout << "\t'best-worst-file' israso geriausius ir blogiausius studentus i atskirus failus.\n";
	cout << "\t'del-stud' sunaikina visas duomenu strukturas.\n";
	cout << "\t'end' israso rezultatus ir baigia darba.\n";
}


//opens ifstream file specified with name
void openFile(ifstream& file, const string name)
{
	file.close();
	file.open(name, std::fstream::in);	//else open in input mode
	if (!file.is_open())
		throw "Error: can't open file";

	if (file.is_open())
	{
		file.clear();
		file.seekg(0, std::ios::beg);
	}
}

//opens file
void openFile(ifstream& file)
{
	file.clear();
	file.seekg(0, std::ios::beg);
}


//function generates a file for future inputs
void generateFile(ofstream& file, const int count)
{
	std::random_device rd;	//initialize random device
	std::mt19937 mt(rd());	//seed mt engine
	std::uniform_int_distribution<int> dist1(1, 10);	//set uniform distribution for homework marks
	std::uniform_int_distribution<int> dist2(0, 50);	//set uniform distribution for homework amount
	if (file.is_open())
	{
		for (int i = 0; i < count; i++)
		{
			file << "Vardas" << i << " Pavarde" << i;
			int randomness = dist2(mt);
			for (int j = 0; j < randomness; j++)
				file << " " << dist1(mt);
			file << "\n";
		}
		cout << "Failas sekmingai sugeneruotas su " << count << " objektu.\n\n";
		file.close();
	}
	else
		throw "Error: Can't read file.";
}



//function checks if the given string is a number
bool checkIfStrIsNum(const string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}



//function gets input and stores to student array
#ifdef VECTOR
void getInput(vector<Student> &student)
#endif

#ifdef LIST
void getInput(list<Student> &student)
#endif

#ifdef DEQUE
void getInput(deque<Student> &student)
#endif
{
	student.push_back(Student());	//push back structure array
	int count = student.size() - 1;	//get count of student
	cout << "STUDENT SIZE: " << student.size() << "\n";

	for (auto it = student.begin(); it != student.end(); ++it)
	{
		it++;
		if (it == student.end())	//if final student is reached
		{
			it--;

			//get name
			cout << "Iveskite studento varda: ";
			cin >> it->name;

			//get surname
			cout << "Iveskite studento pavarde: ";
			cin >> it->surname;


			//begin of 'input homework'
			cout << "Dabar veskite namu darbu rezultatus (minimali verte 1, maksimali 10).\n";
			cout << "Atsitiktiniam namu darbu ir egzaminu rezultatu sugeneravimui, rasykite \"rand\".\n";
			cout << "Kai baigsite, iveskite \"egz\": ";
			string temp_input;
			while (temp_input != "egz")
			{
				cin >> temp_input;

				//break if input is 'egz'
				if (temp_input == "egz")
					break;

				//begin of 'randomize homework results'
				if (temp_input == "rand")
				{
					int max_rand = 20;	//20 is maximum amount of homework currently
					//begin of 'rand error message'
					//if homework amount is 20 or more, don't randomize
					if (max_rand - it->hw.size() < 1)
					{
						cout << "Negeneruojama, kai yra virs " << max_rand << " namu darbu.";
						continue;
					}
					//end of 'rand error message'

					int rand_hw_num = rand() % (max_rand - it->hw.size());	//get random homework amount

					//set randomized marks to homeworks and then exam
					for (int i = 0; i < rand_hw_num; i++)
						it->hw.push_back(1 + rand() % 10);	//randomize between 1 and 10
					it->egz = 1 + rand() % 10;	//randomize exam

					return;
				}
				//end of 'randomize homework results'

				//get mark input
				if (temp_input == "1" || temp_input == "2" || temp_input == "3" || temp_input == "4" || temp_input == "5" || temp_input == "6"
					|| temp_input == "7" || temp_input == "8" || temp_input == "9" || temp_input == "10")//if the input is between 1 and 10 inclusive
					it->hw.push_back(std::stoi(temp_input));	//add to hw array
				//if invalid character is inputed throw error message
				else
				{
					student.pop_back();	//delete the invalid object
					throw "Invalid character(s). Expected numbers between 1 and 10.";
				}
			}
			//end of 'input homework'

			//begin of 'input of exam'
			cout << "Iveskite egzamino rezultata (nuo 1 iki 10): ";
			while (1)
			{
				cin >> temp_input;
				if (temp_input == "1" || temp_input == "2" || temp_input == "3" || temp_input == "4" || temp_input == "5" || temp_input == "6"
					|| temp_input == "7" || temp_input == "8" || temp_input == "9" || temp_input == "10")//if the input is between 1 and 10 inclusive
					break;
				cout << "Klaida. Neteisingas egzamino rezultato formatas. Iveskite egzamino rezultata (nuo 1 iki 10): ";
			}

			if (temp_input != "10")
				it->egz = std::stoi(temp_input);
			else
				it->egz = 10;
			//end of 'input of exam'
		}
		else
			it--;
	}
}


//function returns a substring of single word
int getUntilWhitespace(const string str)
{
	int index = 0;	//index of file_str to point to characters
	while (str[index] != ' ')	//search for whitespace
	{
		index++;	//increment by one
		if (index >= str.length())	//check if array access violations are not broken
			break;
	}
	return index;
}


int getExam(string& str)
{
	while (str.length() > 0)
	{
		//begin of 'delete whitespaces at the end'
		while (str[str.length() - 1] == ' ')
			str.erase(str.length() - 1, 1);
		//end of 'delete whitespaces at the end'

		//begin of 'search for valid number'
		//the idea is to search for digits and try to identify them. Any other symbols - we don't care and we delete them
		int temp_index = 1, temp_length = str.length() - 1 - temp_index;
		if (temp_length >= 0)	//temp_length should be atleast 0, in order to avoid accessing incorrect memory
			while (str[str.length() - 1 - temp_index] != ' ' && str[str.length() - 1 - temp_index] != '1')	//add count to temp_index if wrong characters found
				temp_index++;
		//if any bad characters found, then erase them
		if (temp_index > 1)
			str.erase(str.length() - temp_index + 1, temp_index);	//erase bad characters
		//end of 'search for valid number'

		//begin of 'check if is digit'
		if (isdigit(str[str.length() - 1]))	//if last character is digit
		{
			//begin of 'if 0 found'
			if (str[str.length() - 1] == '0')	//if found 0
			{
				if (str[str.length() - 2] == '1')	//if found 1 before 0
				{
					if (str.length() > 3)
						str.erase(str.length() - 3, 3);	//erase whitespace and two last characters
					else
						str.clear();
					return 10;	//return 10 mark
				}
				str.erase(str.length() - 1, 1);
				continue;
			}
			//end of 'if 0 found'

			//begin of 'if other digit found'
			if (str[str.length() - 1] != '0')	//if found any other digit
			{
				int mark = str[str.length() - 1] - '0';	//specific digit as mark

				if (str.length() == 1)	//if last character left
					str.clear();	//erase last character

				else if (str.length() - 2 > 0)
					str.erase(str.length() - 2, 2);	//erase whitespace and last character

				return mark;	//return mark
			}
			//end of 'if other digit found'
		}
		//end of 'check if is digit'

		//if not a digit found, just erase the symbol
		else
			str.erase(str.length() - 1, 1);
	}
}


//function reads from 'filename.txt'
#ifdef VECTOR
void readFromFile(ifstream& file, vector<Student> &student)
#endif

#ifdef LIST
void readFromFile(ifstream& file, list<Student> &student)
#endif

#ifdef DEQUE
void readFromFile(ifstream& file, deque<Student> &student)
#endif
{


	/*----------------STRUCTURE OF kursiokai.txt------------------------
	Pavarde     Vardas      ND1  ND2   ND3  ND4  ND5 ...  Egzaminas
	Vardas1     Pavarde1    8    9     10   6    10  ...  9
	Vardas2     Pavarde2    7    10    8    5    4   ...  6
	*/

	//begin of 'if file open'
	if (file.is_open())
	{
		string file_str;	//temporary string holding file's lines
		//std::getline(kursiokai, file_str);
		//cout << file_str << "\n";
		//begin of 'read from kursiokai'
		while (std::getline(file, file_str))	//getlines until eof
		{
			Student temp_stud;
			
			//int student_count = student.size() - 1;	//counter to track indexes

			//begin of 'character scan from file_str'
			//begin of 'get name'
			int str_index = getUntilWhitespace(file_str);	//returns (name) character count of a single word substring
			temp_stud.name.append(file_str, 0, str_index);	//append name to structure
			file_str.erase(0, str_index + 1);	//delete name from temporary file_str string
			//end of 'get name'

			//cout << student[student_count].name << "\n";

			//begin of 'get surname'
			str_index = getUntilWhitespace(file_str);	//returns (surname) character count of a single word substring
			temp_stud.surname.append(file_str, 0, str_index);	//append surname to structure
			file_str.erase(0, str_index + 1);	//delete name from temporary file_str string
			//end of 'get surname'


			//get value of the exam
			temp_stud.egz = getExam(file_str);

			//begin of 'get homework'
			str_index = 0;	//reset index
			while (file_str.length() > 0)	//search for homework results between whitespaces
			{
				//begin of 'if digit found'
				if (isdigit(file_str[str_index]))	//if found digit
				{
					//begin of 'any digit but 1'
					if (file_str[str_index] != '1' && file_str[str_index] != '0')	//if found any digit but '1'
					{
						if (file_str[str_index + 1] == ' ' || file_str[str_index + 1] == '.' || file_str.length() == 1)	//if the digit is followed by whitespace or found last character
							temp_stud.hw.push_back(file_str[str_index] - '0');	//push back into student homework the mark
						//else means there's junk we should erase
						else
							while (file_str[str_index] != ' ' && file_str.length() > 0)
								file_str.erase(str_index, 1);
					}
					//end of 'any digit but 1'

					//begin of 'found 1'
					if (file_str[str_index] == '1')	//if found '1'
					{
						if (file_str[str_index + 1] == ' ')	//if 1 is followed by whitespace
							temp_stud.hw.push_back(1);	//push back 1
						else if (file_str[str_index + 1] == '0')	//if 1 is followed by 0
						{
							if (file_str[str_index + 2] == ' ' || file_str.length() == 2)	//if 10 is followed by whitespace or found last 2 characters
								temp_stud.hw.push_back(10);	//push back 10
						}
						//else means there's junk we should erase
						else
							while (file_str[str_index] != ' ' && file_str.length() > 0)
								file_str.erase(str_index, 1);
					}
					//end of 'found 1'
				}
				//end of 'if digit found'

				//begin of 'last characters of homework found'
				if (file_str.length() == 1 && str_index == 1)	//if reached last character and already manipulated 
					break;	//then break

				//if found 10
				if (file_str.length() == 2 && str_index == 2)	//if 2 characters are last
					if (file_str[0] == '1' && file_str[1] == '0')	//if those are 1 and 0
						break;	//then break
				//end of 'last characters of homework found'

				//if the whitespace is found, delete from string beginning up to whitespace inclusive
				if (file_str[str_index] == ' ')	//if found whitespace
				{
					file_str.erase(0, str_index + 1);	//delete the pushed back homework from temporary string
					str_index = 0;	//reset index
					continue;	//go next
				}

				//if found dot
				if (file_str[str_index] == '.')
				{
					str_index = 0;
					while (file_str[str_index] != ' ' && file_str.length() > 0)
						file_str.erase(str_index, 1);
					str_index = 0;
					continue;
				}



				str_index++;	//increment by 1
			}
			//end of 'get homework'
			//end of 'character scan from file_str'

			//cout << "sizeof: " << sizeof(temp_stud) << "\n";
			student.push_back(Student(temp_stud));	//push back
		}
		//end of 'read from kursiokai'
	}
	//end of 'if file open'
	//begin of 'if file is not open'
	else
		throw "Klaida: neimanoma atidaryti failo.\n";
	//end of 'if file is not open'

}


//function returns the avarage value of the vector array
#ifdef VECTOR
double avgCalc(const vector<int> hw, const int egz)
#endif

#ifdef LIST
double avgCalc(const list<int> hw, const int egz)
#endif

#ifdef DEQUE
double avgCalc(const deque<int> hw, const int egz)
#endif
{
	//calculate the sum of array and return the average
	int sum = 0;
	for (auto const& i : hw)
		sum += i;

	if (hw.size() != 0)	//skip division by 0
	{
		double avg = 0.4*(double)((double)sum / (double)hw.size()) + 0.6*egz;
		if (avg < 0 || avg > 10)
			return 0;
		return avg;
	}
	if (hw.size() == 0 && egz >= 1 && egz <= 10)	//if no homeworks are done, but atleast exam is passed
		return egz;
	return 0;
}


//function returns the median value of the vector array
#ifdef VECTOR
double medCalc(vector<int> hw, const int egz)
#endif

#ifdef LIST
double medCalc(list<int> hw, const int egz)
#endif

#ifdef DEQUE
double medCalc(deque<int> hw, const int egz)
#endif
{
	//we need to sort the array in ascending order
#ifndef LIST
	std::sort(hw.begin(), hw.end());

	int sz = hw.size() / 2;
	int *it = &sz;
#endif

#ifdef LIST
	hw.sort();

	std::list<int>::iterator it = hw.begin();
	std::advance(it, std::distance(hw.begin(), hw.end()) / 2);
#endif

	//if odd
	if (hw.size() % 2 == 1)
	{
		//double med = 0.4*(double)hw[hw.size() / 2] + 0.6*egz;
		double med = 0.4*(double)(*it) + 0.6*egz;
		if (med < 0 || med > 10)
			return 0;
		return med;
	}

	//if even
	if (hw.size() % 2 == 0)
	{
		if (hw.size() != 0)	//skip division by 0
		{
			//double med = 0.4*((1.0*hw[hw.size() / 2 - 1] + 1.0*hw[hw.size() / 2]) / 2) + 0.6*egz;
			double med = 0.4*((1.0*(*(--it)) + 1.0*(*(++it))) / 2) + 0.6*egz;
			if (med < 0 || med > 10)
				return 0;
			return med;
		}
		if (hw.size() == 0 && egz >= 1 && egz <= 10)	//if no homeworks are done, but atleast exam is passed
			return egz;
		return 0;
	}


	return 0;
}


//function picks students with higher or equal average final mark than 5 and puts them into 'cool' vector, otherwise in the 'loser' vector
#ifdef VECTOR
void sortBestWorst(const vector<Student>& student, vector<Student>& cool, vector<Student>& lame)
#endif

#ifdef LIST
void sortBestWorst(const list<Student>& student, list<Student>& cool, list<Student>& lame)
#endif

#ifdef DEQUE
void sortBestWorst(const deque<Student>& student, deque<Student>& cool, deque<Student>& lame)
#endif
{
	if (student.size() == 0)
		throw "Error: main vector size is 0.";

	//reserve capacity trying to avoid size reallocation for vector type
#ifdef VECTOR
	cool.reserve(student.capacity());
	lame.reserve(student.capacity());
#endif

	//cout << sizeof(student) << "\n";

	for (auto & it : student)
	{
		if (it.avg_final >= 5 && it.avg_final <= 10)	//if avg is not lower than 5, the student is considered cool
		{
			Student temp;	//temporary object

			//copy only neccessary data
			temp.name = it.name;
			temp.surname = it.surname;
			temp.avg_final = it.avg_final;
			temp.med_final = it.med_final;

			cool.push_back(temp);	//push back temp object
			continue;
		}
		if (it.avg_final > 0 && it.avg_final < 5)	//if avg is lower than 5, the student is considered loser
		{
			Student temp;	//temporary object

			//copy only neccessary data
			temp.name = it.name;
			temp.surname = it.surname;
			temp.avg_final = it.avg_final;
			temp.med_final = it.med_final;

			lame.push_back(temp);	//push back temp object
		}
	}
	//shrink to fit (save memory)
#ifndef LIST
	cool.shrink_to_fit();
	lame.shrink_to_fit();
#endif
}



//function picks students with lower average final mark than 5 and puts them into 'lame' vector, otherwise leave them
#ifdef VECTOR
void sortBestWorst2(vector<Student>& student, vector<Student>& lame)
#endif

#ifdef LIST
void sortBestWorst2(list<Student>& student, list<Student>& lame)
#endif

#ifdef DEQUE
void sortBestWorst2(deque<Student>& student, deque<Student>& lame)
#endif
{
	if (student.size() == 0)
		throw "Error: main vector size is 0.";

	//reserve capacity trying to avoid size reallocation for vector type
#ifdef VECTOR
	lame.reserve(student.capacity());
#endif

	//cout << sizeof(student) << "\n";
	int index = 0;
	auto it = student.begin();
	//for (auto & it : student)
	for (it; it != student.end(); ++it)
	{
		if (it->avg_final >= 0 && it->avg_final < 5)	//if avg is lower than 5, the student is considered loser
		{
			if (it->avg_final != 0)
			{
				Student temp;	//temporary object
				//copy only neccessary data
				temp.name = it->name;
				temp.surname = it->surname;
				temp.avg_final = it->avg_final;
				temp.med_final = it->med_final;

				lame.push_back(temp);	//push back temp object
			}


			//student.erase(student.begin() + index);
#ifdef LIST
			it = student.erase(it);
			it--;
#endif

#ifndef LIST
			student.erase(it);
			it--;
#endif
			//index--;
		}
		//index++;
	}
	//shrink to fit (save memory)
#ifndef LIST
	student.shrink_to_fit();
	lame.shrink_to_fit();
#endif
}



//function write best students to one file, and lame students to another file
#ifdef VECTOR
void writeToFileBestWorst(const string ofstreamName_temp, const vector<Student>& cool, const vector<Student>& lame)
#endif

#ifdef LIST
void writeToFileBestWorst(const string ofstreamName_temp, const list<Student>& cool, const list<Student>& lame)
#endif

#ifdef DEQUE
void writeToFileBestWorst(const string ofstreamName_temp, const deque<Student>& cool, const deque<Student>& lame)
#endif
{
	//create file of cool
	string file_name = "cool_" + ofstreamName_temp + ".txt";
	ofstream file_cool(file_name);	//create output file

	//write data to file
	if (file_cool.is_open())	//if file_cool is open
		for (auto const& it : cool)
			file_cool << it.name << " " << it.surname << " " << std::fixed << std::setprecision(2) << it.avg_final << "\n";	//output data of cool students
	//else error
	else
	{
		file_cool.clear();	//clear
		file_cool.close();	//close
		throw "Error: can't create new file cool_x.txt.";
	}
	file_cool.close();	//close file

	////begin of 'open cool_x.txt'
	//string open_cool = "notepad \"" + file_name + "\"";
	//char openC[255];
	//strcpy_s(openC, open_cool.c_str());
	//system(openC);
	////end of 'open cool_x.txt'

	//create file of lame
	file_name = "lame_" + ofstreamName_temp + ".txt";
	ofstream file_lame(file_name);	//create output file

	//write data to file
	if (file_lame.is_open())	//if file_lame is open
		for (auto const& it : lame)
			file_lame << it.name << " " << it.surname << " " << std::fixed << std::setprecision(2) << it.avg_final << "\n";	//output data of lame students
	//else error
	else
	{
		file_lame.clear();	//clear
		file_lame.close();	//close
		throw "Error: can't create new file lame_x.txt.";
	}
	file_lame.close();

	////begin of 'open lame_x.txt'
	//string open_lame = "notepad \"" + file_name + "\"";
	//char openL[255];
	//strcpy_s(openL, open_lame.c_str());
	//system(openL);
	////end of 'open lame_x.txt'
}


//delete student object vector
#ifdef VECTOR
void deleteStudentVector(vector<Student>& v)
#endif

#ifdef LIST
void deleteStudentVector(list<Student>& v)
#endif

#ifdef DEQUE
void deleteStudentVector(deque<Student>& v)
#endif
{
	//delete homework vectors
	for (auto& elem : v)
	{
		elem.hw.clear();
		elem.hw.resize(0);
#ifndef LIST
		elem.hw.shrink_to_fit();
#endif
		if (!elem.hw.empty())
			throw "Error: homework array could not have been deleted.";
	}
	//delete student object vector
	v.clear();
	v.resize(0);
#ifndef LIST
	v.shrink_to_fit();
#endif
	if (!v.empty())
		throw "Error: student array could not have been deleted.";
}


//function used in sorting function to compare string characters
bool compareNames(Student &a, Student &b)
{
	//compare by name
	if (a.name.size() < b.name.size())
		for (int i = 0; i < a.name.size(); i++)
			if (a.name[i] != b.name[i])
				return b.name[i] > a.name[i];

	//else
	return b.name[0] > a.name[0];
}

//returns required setw amount for names
#ifdef VECTOR
int longestName(vector<Student> student)
#endif

#ifdef LIST
int longestName(list<Student> student)
#endif

#ifdef DEQUE
int longestName(deque<Student> student)
#endif
{
	int longest = 0;
	for (auto const& it : student)
		if (it.name.length() > longest)
			longest = it.name.length();
	return longest;
}


//returns required setw amount for surnames
#ifdef VECTOR
int longestSurname(vector<Student> student)
#endif

#ifdef LIST
int longestSurname(list<Student> student)
#endif

#ifdef DEQUE
int longestSurname(deque<Student> student)
#endif
{
	int longest = 0;
	for (auto const& it : student)
		if (it.surname.length() > longest)
			longest = it.surname.length();
	return longest;
}


//function prints output of stucture student
#ifdef VECTOR
void printOutput(vector<Student>& student)
#endif

#ifdef LIST
void printOutput(list<Student>& student)
#endif

#ifdef DEQUE
void printOutput(deque<Student>& student)
#endif
{


#ifndef LIST
	std::sort(student.begin(), student.end(), compareNames);	//sort structures
#endif

#ifdef LIST
	student.sort(compareNames);
#endif

	//get lengths of the longest setw required
	int setw_name_lenght = longestName(student) + 2;	//for names
	int setw_surname_lenght = longestSurname(student) + 2;	//for surnames

	//outputing results
	cout << "\n\n";
	cout << std::setw(setw_surname_lenght) << std::left << "Pavarde";
	cout << " " << std::setw(setw_name_lenght) << std::left << "Vardas";
	cout << " " << std::setw(10) << std::left << "VidGalut";
	cout << " " << std::setw(10) << std::left << "MedGalut\n";
	for (int i = 0; i < setw_name_lenght + setw_surname_lenght + 10 + 10; i++)
		cout << '-';
	cout << "\n";
	//print the results of all students
	for (auto const& it : student)
	{
		cout << std::setw(setw_surname_lenght) << std::left << it.surname;
		cout << " " << std::setw(setw_name_lenght) << std::left << it.name;
		cout << " " << std::setw(10) << std::left << std::fixed << std::setprecision(2) << it.avg_final;
		cout << " " << std::setw(10) << std::left << std::fixed << std::setprecision(2) << it.med_final << "\n";
	}
	cout << "\nJei rezultatai lygus 0, vadinasi ivestis yra bloga.\n";
}
