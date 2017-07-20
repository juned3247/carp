#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
char* basename;
string argsofcommand;
inline bool exists (const string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
void print_ask_help() {
	cout<<endl<<"Try '"<<basename<<" --help' for more information.";
}
void print_missing_operand() {
	cout<<basename<<": missing operand";
	print_ask_help();
}
void print_many_operand() {
	cout<<basename<<": Only one argument can be supplied";
	print_ask_help();
}
void print_help() {
	cout<<"Usage: "<<basename<<" FILENAME"<<endl;
	cout<<"Compile and run FILENAME named C++ or JAVA Program.";
}
void print_not_exist() {
	cout<<basename<<": No such file or directory";
}
void run_file_cpp() {
	string tempfile = "/home/" + (string)getenv("USER") + "/.cache/tempcpp";
	const char* char_tempfile = tempfile.c_str();
	if (exists(char_tempfile)) {
		string cpprun = "~/.cache/tempcpp" + argsofcommand;
		system(cpprun.c_str());
		system("rm ~/.cache/tempcpp");
	}
}
void car_cpp(char* file) {
	if (exists(file)) {
		string command = "g++ " + (string)file + " -o ~/.cache/tempcpp";
		const char* char_cpp_command = command.c_str();
		system(char_cpp_command);
		run_file_cpp();
	} else {
		print_not_exist();
	}
}
void run_file_c() {
	string tempfile = "/home/" + (string)getenv("USER") + "/.cache/tempc";
	const char* char_tempfile = tempfile.c_str();
	if (exists(char_tempfile)) {
		string cpprun = "~/.cache/tempc" + argsofcommand;
		system(cpprun.c_str());
		system("rm ~/.cache/tempc");
	}
}
void car_c(char* file) {
	if (exists(file)) {
		string command = "gcc " + (string)file + " -o ~/.cache/tempc";
		const char* char_c_command = command.c_str();
		system(char_c_command);
		run_file_c();
	} else {
		print_not_exist();
	}
}
void run_file_java(string filename) {
	size_t lastindex = filename.find_last_of("."); 
	string name_without_ext = filename.substr(0, lastindex);
	string cachedir = "/home/" + (string)getenv("USER") + "/.cache";
	string tempjavafile = "/home/" + (string)getenv("USER") + "/.cache/" + name_without_ext + ".class";
	const char* char_tempjavafile = tempjavafile.c_str();
	if(exists(char_tempjavafile)) {
		string run_command = "java  -cp " + cachedir + " " + name_without_ext + argsofcommand;
		system(run_command.c_str());
		string delete_command = "rm " + tempjavafile;
		system(delete_command.c_str());
	}
}
void car_java(char* file) {
	if(exists(file)) {
		string command = "javac " + (string)file + " -d ~/.cache/";
		const char* char_java_command = command.c_str();
		system(char_java_command);
		run_file_java(file);
	} else {
		print_not_exist();
	}
}
string get_extension(char* name) {
	string string_name(name);
	string ext = string_name.substr(string_name.find_last_of(".") + 1);
	return ext;
}
int main(int argc, char *argv[]) {
	basename = argv[0];
	switch(argc) {
		case 1:
			print_missing_operand();
			break;
		default:
			if((string) argv[1] == "--help"){   // argv[1] == "--help" was not working
				print_help();
			} else {
				for(int i=2; i<argc; i++) {
					argsofcommand = argsofcommand + " " + argv[i];
				}
				if (get_extension(argv[1]) == "cpp") {
					car_cpp(argv[1]);
				} else if(get_extension(argv[1]) == "java") {
					car_java(argv[1]);
				} else if(get_extension(argv[1]) == "c") {
					car_c(argv[1]);
				} else {
					cout<<"file type not supported.";
				}
			}
		/*	break;
		default:
			print_many_operand();*/
	}
	cout<<endl;
	return 0;
}