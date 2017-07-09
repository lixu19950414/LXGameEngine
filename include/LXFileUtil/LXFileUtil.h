/*
 *  FileUtil.hpp
 *  FileUtil
 *
 *  Created by duoyi on 2017/6/29.
 *  Copyright © 2017年 lixu. All rights reserved.
 *
 */

#ifndef FileUtil_
#define FileUtil_

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

/* The classes below are exported */

namespace LX_FU {

    /**
     * Global path prefix of fileutil to fix relative paths.
     *
     */
    static std::string g_strPathPrefix = "/";

	/**
	* Set global path prefix of fileutil to fix relative paths.
	*
	*/
    void setPathPrefix(const std::string& path);
    
	/**
	* Get global path prefix of fileutil to fix relative paths.
	*
	*/
    std::string getPathPrefix();
    
	/**
	* Get absolute path of a path according to path prefix.
	*
	*/
    std::string getAbsolutePath(const std::string& relativePath);
    
	/**
	* Judge whether the given path is absolute path or not.
	*
	*/
    bool isAbsolutePath(const std::string& path);

	/**
	* Get the directory of a path.
	*
	*/
	std::string getDirectory(const std::string& path);

	/**
	* Get file name of a path.
	*
	*/
	std::string getFileName(const std::string& path);

	/**
	* Create directories if the given path not exists.
	*
	*/
	bool makeDirectories(const std::string& path);

	/**
	* Create directories if the given path not exists.
	*
	*/
	class Data {
	public:
		Data();
		~Data();
		bool initFromFile(const std::string& path);
		inline std::string getString() { return _sstream.str(); };
		inline int getDataLen() { return _sstream.str().length(); };
		inline bool loadSucceed() { return _loadSucceed; };
	private:
		std::stringstream _sstream;
		bool _loadSucceed;
	};

	/**
	* Create directories if the given path not exists.
	*
	*/
	Data* getDataFromFile(const std::string& path);
    
}

#endif
