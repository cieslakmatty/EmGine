#pragma once

#include <vector>
#include <fstream>

namespace EmGine{

class IOManager{

public:
	static IOManager* Instance();

	bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);

private:
	IOManager(){}
	IOManager(IOManager const&){};
	IOManager& operator=(IOManager const&){};

	static IOManager* m_pInstance;
};

}