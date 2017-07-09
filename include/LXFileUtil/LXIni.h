//
//  Ini.hpp
//  FileUtil
//
//  Created by duoyi on 2017/6/29.
//  Copyright © 2017年 lixu. All rights reserved.
//

#ifndef Ini_hpp
#define Ini_hpp

#include <map>
#include <string>

namespace LX_FU {
    /**
     * INI files handlers.
     *
     * Name space LX_FU::INI
     * getIniConfigMap & saveIniConfigFile
     *
	 * @warning One line's size should not be greater than 32
     */
    
    namespace INI {
        
        class IniConfig
        {
            
        public:
            IniConfig();
            IniConfig(const std::string& configName);
            ~IniConfig();
            
			/**
			* Save the current config map to file.
			* If the file do not exists, this will create the file.
			*
			* @warning this will overwrite the file in existance.
			*/
            bool saveToFile(const std::string& configName);

			/**
			* Load configs from a file.
			*
			*/
            bool loadFromFile(const std::string& configName);
            
			/**
			* Judge whether current configs contains key of confName or not.
			*
			*/
            bool hasConf(const std::string& confName);

			/**
			* Get the value of confName, return "" if do not have this config.
			*
			*/
            std::string getConf(const std::string& confName);

			/**
			* Set key->value to this ini config.
			*
			*/
            void setConf(const std::string& key, const std::string& value);
            
            
        private:
            std::map<std::string, std::string> m_mapIni;
        };
        
        IniConfig readIniConfigFromFile(const std::string& configName);
        
        bool saveIniConfigToFile(IniConfig& iniConfig, const std::string& configName);
    }
}


#endif /* Ini_hpp */
