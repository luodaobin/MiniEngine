#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_
#include <queue>

template<typename TObject>
class ObjectPool
{
public:
	static const unsigned int  cuChunkSize=100;
	TObject * Create()
	{
		TObject* temp = TakeOne();
		temp = new(temp) TObject();
		return temp;
	}
	TObject * Create(TObject& rObject)
	{
		TObject* temp = TakeOne();
		temp = new(temp) TObject(rObject);
		return temp;
	}
	void Release(TObject * pObject)
	{
		pObject->~TObject();
		m_qFreeList.push(pObject);
	}
	ObjectPool()
	{
		AllocateChunk();
		m_iCounter=0;
	}
	~ObjectPool()
	{
		for(unsigned int ii=0;ii<m_vChunks.size();ii++)
		{
			delete [] m_vChunks[ii];
		}
	}
private:
	 unsigned int m_iCounter;
	void AllocateChunk()
	{
		char * pChunk=new char[sizeof(TObject)*cuChunkSize];
		m_vChunks.push_back(pChunk);
		for (int i = 0 ; i < cuChunkSize ; i++)
		{
			TObject* pTemp = (TObject*)(pChunk+i*sizeof(TObject));
			m_qFreeList.push(pTemp);
		}
	}
	TObject * TakeOne()
	{
		m_iCounter++;
		if (m_qFreeList.empty())
		{ 
			AllocateChunk(); 
		}

		TObject* temp = m_qFreeList.front();
		m_qFreeList.pop();
		return temp;
	}


	std::queue<TObject*> m_qFreeList;
	std::vector<char*> m_vChunks;

};
#endif

