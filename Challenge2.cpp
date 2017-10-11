#include <iostream>
#include <cstring>
#include <fstream>

#include <sys/stat.h>
#include <dirent.h>

using namespace std;

void copyFile(string ifilepath, string ofilepath, ifstream& inputfile, ofstream& outputfile)
{
	inputfile.open(ifilepath.c_str());
	outputfile.open(ofilepath.c_str());

	inputfile.seekg(0,inputfile.end);
	long size = inputfile.tellg(); //Record the length of the file in bytes
	inputfile.seekg(inputfile.beg); //Put pointer for reading at the beginning of the file
	char* fbyte = new char[size]; //Record how many bytes are needed for writing

	inputfile.read(fbyte,size);
	outputfile.write(fbyte,size);

	inputfile.close();
	outputfile.close();
}

void copyFolder(string srcfolder, string tgtfolder, string extign)
{
	ifstream inputfile;
	ofstream outputfile;
	string ifilepath, ofilepath;
	string extcheck = "";
	
	struct stat filestat; //Only used to check if file is a directory
	
	DIR *src;
	dirent *srcent;
	src = opendir(srcfolder.c_str()); //Open the correct directory
	srcent = readdir(src); //Read the directory
	
	do
	{
		if (strcmp(srcent->d_name,".")!= 0 && strcmp(srcent->d_name,"..") != 0) //Do not include current folder or partent folder references
		{
			
			ifilepath = srcfolder + '/' + string(srcent->d_name);
			ofilepath = tgtfolder + '/' + string(srcent->d_name);
			
			stat(ifilepath.c_str(), &filestat); //Record the status of the current file
			
			if (S_ISDIR(filestat.st_mode)) //If the current file is a folder
			{
				mkdir(ofilepath.c_str(), S_IRUSR | S_IWUSR | S_IXUSR); //Create a new folder in the target destination with same name and user permissions
				copyFolder(ifilepath, ofilepath, extign); //Recursively call the function to copy all files in subdirectories
			}
			else //If the current file is not a folder
			{
				for(int i = extign.length(); i  > 0; i--)
				{
					extcheck += string(srcent->d_name)[string(srcent->d_name).length()-i];
				} //Checking if the current file extension is that which should be ignored
				if (extcheck != extign || extign.empty()) copyFile(ifilepath, ofilepath, inputfile, outputfile); //Dont copy if it should be ignored or if no extension was specified
				extcheck.clear(); //Clear checking string for next file
			}
		}
	} while (srcent = readdir(src)); //While files still exist within the folder keep iterating
	
	closedir(src);
}



int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "Input 2 folders" << endl;
		return -1;
	} //Make sure there is an input and output folder
	
	string srcfolder = argv[1];
	string tgtfolder = argv[2];
	string extign;
	
	if (argv[3]) extign = argv[3]; //Check 3rd argument for ignored extension
	else if (!argv[3]) extign.clear(); //If none is provided do not ignore any files
	
	
	copyFolder(srcfolder, tgtfolder, extign);
}