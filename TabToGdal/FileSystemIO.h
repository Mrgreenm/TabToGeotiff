#pragma once
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost\filesystem.hpp" 
#include <iostream>
#include <string>
#include <vector>

namespace bfs = boost::filesystem;

class FileSystemIO
{
public:
	FileSystemIO();
	~FileSystemIO();
	static std::vector<bfs::directory_entry>* GetFolderList();
	static bool isMapFilesExists(const bfs::path p);
	static std::string GetFirstWithExtention(const bfs::path&, const std::string &Extention);
	static std::string GetFileByName(const bfs::path&, const std::string &fileName);
	static std::vector<std::string>* GetFileList(bfs::path&);
	static std::vector<std::string> GetCoords(const bfs::path path, const std::string & fileName);
	static void writeCoordsToFile(const std::vector<std::string> &CoordsVector, const std::string &fileName);
	static std::vector<std::string> ReadSettings();
};

