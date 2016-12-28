#include "Document.h"

Document::Document()
{
}

Document::Document(System* system, int headIndex, CCString name, string path, int adress, int memoryLong)
{
	this->system = system;
	this->headIndex = headIndex;
	this->name = name;
	this->adress = adress;
	this->memoryLong = memoryLong;
	this->isLive = true;
	this->setPath(path);
}

Document::~Document()
{
}

void Document::setAdress(int adress)
{
	this->adress = adress;
}

int Document::getAdress()
{
	return this->adress;
}

void Document::setMemoryLong(int memoryLong)
{
	this->memoryLong = memoryLong;
}

int Document::getMemoryLong()
{
	return this->memoryLong;
}

void Document::deleteSelf()
{
	// ��ȡϵͳ��Ϣ
	int* head = this->system->getHead();
	linkItem* link = this->system->getFileArr();
	Vector<SystemFile*> fileVec = this->system->getFileVec();
	Vector<freeMemory*> freeMemoryArr = this->system->getFreeMemoryArr();
	std::map<int, int> fileToVec = this->system->getFileToVec();

	this->isLive = false;
	// Ӳ����ɾ�����ļ�
	string filename = this->path;
	filename = filename + ".txt";
	string command = "del " + filename;
	std::system(command.c_str());

	// ά���ڴ��
	bool flag = true;
	int position = fileToVec[this->headIndex];
	freeMemoryArr.at(position)->setType(0);

	int behind = position - 1;
	while (behind > 1 && freeMemoryArr.at(behind)->getType() == 2)
	{
		behind--;
	}
	int front = position + 1;
	while (front + 1 < freeMemoryArr.size() && freeMemoryArr.at(front)->getType() == 2)
	{
		front++;
	}

	if (behind >= 0 && freeMemoryArr.at(behind)->getType() == 0)
	{
		freeMemoryArr.at(behind)->setLong(freeMemoryArr.at(behind)->getLong() + fileVec.at(num)->getMemoryLong());
		freeMemoryArr.at(position)->setType(2);
		flag = false;
	}
	if (front < freeMemoryArr.size() && freeMemoryArr.at(front)->getType() == 0)
	{
		if (!flag)
		{
			freeMemoryArr.at(behind)->setLong(freeMemoryArr.at(behind)->getLong() + freeMemoryArr.at(front)->getLong());
			freeMemoryArr.at(position)->setType(2);
			freeMemoryArr.at(front)->setType(2);
		}
		else
		{
			freeMemoryArr.at(position)->setLong(freeMemoryArr.at(position)->getLong() + freeMemoryArr.at(front)->getLong());
			freeMemoryArr.at(front)->setType(2);
		}
	}
}

bool Document::create(Folder* father, CCString name)
{
	// ��ȡϵͳ��Ϣ
	System* thisSystem = father->getSystem();
	int* head = thisSystem->getHead();
	linkItem* link = thisSystem->getFileArr();
	Vector<SystemFile*> fileVec = thisSystem->getFileVec();
	int fileArrNum = thisSystem->getFileArrNum();
	Vector<freeMemory*> freeMemoryArr = thisSystem->getFreeMemoryArr();
	std::map<int, int> fileToVec = thisSystem->getFileToVec();

	if (father->checkName(name))
	{
		Document * doc = new Document(thisSystem, thisSystem->getFileVec.size(), name, father->getPath(), -1, 0);
		// ��Ӳ���ϴ������ļ�
		string nameStr = doc->getPath();
		string filename = nameStr + ".txt";

		// ������д����ļ�
		freopen(filename.c_str(), "w", stdout);
		cout << doc->getName().getCString() << ".txt" << endl;
		fclose(stdout);

		// ��ȡ�ļ��Ĵ�С
		const char *filepath = filename.c_str();
		struct _stat info;
		_stat(filepath, &info);
		int size = info.st_size;

		int adress = doc->findAdress(size);
		// �����ڴ�����
		if (adress != -1)
		{
			// �����ڴ��
			int s = freeMemoryArr.at(adress)->getStart();
			int l = freeMemoryArr.at(adress)->getLong();
			freeMemoryArr.at(adress)->setLong(size);
			freeMemoryArr.at(adress)->setType(1);
			freeMemory *f = new freeMemory(s + size, l - size, 0);
			freeMemoryArr.insert(adress + 1, f);

			// ����doc����������
			thisSystem->reduceMemoryLarge(size);
			fileVec.pushBack(doc);
			father->addList(doc->getHeadIndex());
			doc->setMemoryLong(size);
			doc->setAdress(freeMemoryArr.at(adress)->getStart());
			fileToVec[doc->getHeadIndex()] = adress;
		}
		// �������ڴ�����
		else
		{
			string command = "del " + filename;
			std::system(command.c_str());
			doc->setIsLive(false);
			return false;
		}
		return true;
	}
}



