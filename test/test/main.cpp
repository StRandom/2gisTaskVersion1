/*
Ќапишите (консольную) программу, принимающую на вход †им€ файла и набор параметров. 
¬ зависимости от параметров программа должна работать в трЄх режимах:
test -f Test.tst -m words -v mother
печатает количество слов Ђmotherї в файле ЂTest.tstї
test -f Test.tst -m checksum
печатает 32-хбитную чексумму, рассчитанную по алгоритму checksum = word1 + word2 + Е + wordN 
(word1..wordN Ц 32-хбитные слова, представл€ющие содержимое файла)
test -h
печатает информацию о программе и описание параметров.
*/

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

int main(int argc, char * argv[]){
	if (argc < 2){
		// Not enough parameters
		cout << "Not enough parameters. Try 'test -h'." << endl;
		return 0;
	}
	if (strcmp(argv[1], "-h") == 0){
		// Note : [mode3] test -h
		cout << "test, a simple console application." << endl;
		cout << "Usage :\t test -f <file_name> -m words -v <keyword>" << endl;
		cout << "\t test -f <file_name> -m checksum" << endl;
		cout << "\t test -h" << endl;
		cout << "\nStartup :" << endl;
		cout << "-h \t print this help. :" << endl;
		cout << "-f <file_name> -m [OPTION] ... \t work with file <file_name>." << endl;
		cout << "OPTIONS :" << endl;
		cout << "words -v <keyword> \t count the number of words <keyword> in the file." << endl;
		cout << "checksum \t calculate sum of numbers(32-bit) in the file." << endl;
		return 0;
	} else if (strcmp(argv[1], "-f") == 0){
		// test -f ...
		if (argc < 5){
			// Not enough parameters
			cout << "Not enough parameters. Try 'test -h'." << endl;
			return 0;
		}
		// argv[2] is <file_name>
		if (strcmp(argv[3], "-m") == 0){
			if (strcmp(argv[4], "words") == 0){
				if (argc < 7){ 
					cout << "Not enough parameters. Try 'test -h'." << endl;
					return 0;
				}
				if (strcmp(argv[5], "-v") == 0){
					// Note : [mode 1] test -f <file_name> -m words <keyword>
					// argv[6] is <keyword>
					ifstream f;
					int	result = 0;
					char currValue[255];
					f.exceptions (ifstream::failbit | ifstream::badbit);
					try{
						f.open(argv[2]);
						while (!f.eof()){
							f >> currValue;
							if (strcmp(currValue, argv[6]) == 0)
								result++;
						}
					}
					catch (ofstream::failure e){
						cout << "File not found or corrupt." << endl;
						if (f.is_open())
							f.close();
						return 0;
					}
					// The file was successfully opened and read.
					// RESULT : print number of word <keyword>
					cout << result << endl;
					f.close();
					return 0;
				} else {
					// Wrong parameters
					cout << "Wrong parameters. Try 'test -h'." << endl;
					return 0;
				}
			} else if (strcmp(argv[4], "checksum") == 0) {
				// Note : [mode 2] test -f <file_name> -m checksum
				ifstream f;
				__int32	checksum = 0;
				__int32 currValue;
				f.exceptions (ifstream::failbit | ifstream::badbit);
				try {
					f.open(argv[2]);
					while (!f.eof()){
						f >> currValue;
						checksum += currValue;
					}
				}
				catch (ofstream::failure e) {
					cout << "File not found or corrupt." << endl;
					if (f.is_open())
						f.close();
					return 0;
				}
				// The file was successfully opened and read.
				// RESULT : print checksum
				cout << checksum << endl;
				f.close();
				return 0;
			} else {
				// Wrong parameters
				cout << "Wrong parameters. Try 'test -h'." << endl;
				return 0;
			}
		} else {
			// Wrong parameters
			cout << "Wrong parameters. Try 'test -h'." << endl;
			return 0;
		}
	} else {
		// Wrong parameters
		cout << "Wrong parameters. Try 'test -h'." << endl;
		return 0;
	}
	return 0;
}