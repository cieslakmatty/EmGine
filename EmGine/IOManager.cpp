#include "IOManager.h"

namespace EmGine{

IOManager* IOManager::m_pInstance = NULL;

IOManager* IOManager::Instance(){

	if (!m_pInstance){

		m_pInstance = new IOManager;
	}
	return m_pInstance;
}

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer){

	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()){

		perror(filePath.c_str());
		return false;
	}
	//get the file size
	//seek to the end
	file.seekg(0, std::ios::end);
	//get the file size
	int fileSize = file.tellg();
	//seek back to the beginning
	file.seekg(0, std::ios::beg);
	//remove the header
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();
	return true;
}

}