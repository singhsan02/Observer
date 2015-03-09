#include <iostream>
#include <vector>
using namespace std;

class Subject;

class Observer{
public:
	virtual void Update(Subject* thechangeSubject) = 0;
};

class Subject{
public:
	virtual void Attach(Observer*);
	virtual void Dettach(Observer*);
	virtual void Notify();
private:
	vector<Observer*> _observer;
};

void Subject::Attach(Observer* o){
	_observer.push_back(o);
}
void Subject::Dettach(Observer* o){
	int count = _observer.size();
	int i;
	for (i = 0; i < count; ++i){
		if (_observer[i] == o)
			break;
	}
	if (i < count){
		_observer.erase(_observer.begin() + i);
	}
}
void Subject::Notify(){
	cout << "!!Lets Update all the Observers!!" << endl;
	for (int i = 0; i < _observer.size(); ++i)
		(_observer[i])->Update(this);

}

class ClockTimer : public Subject{
public:
	void Tick();
};
void ClockTimer::Tick(){
	cout << "The Clock Ticked. " << endl;
	Notify();
}

class DigitalClock : public Observer{
public:
	DigitalClock(ClockTimer*);
	~DigitalClock();
	void Update(Subject*);
private:
	ClockTimer* _subject;
};
DigitalClock::DigitalClock(ClockTimer* s){
	_subject = s;
	_subject->Attach(this);
}
DigitalClock::~DigitalClock(){
	_subject->Dettach(this);
}
void DigitalClock::Update(Subject* theChangedSubject){
	if (theChangedSubject == _subject){
		cout << "The DigitalClock Observer is Sucessfully Updated!!" << endl;
	}
}

class AnalogClock : public Observer{
public:
	AnalogClock(ClockTimer*);
	~AnalogClock();
	void Update(Subject*);
private:
	ClockTimer* _subject;
};
AnalogClock::AnalogClock(ClockTimer* s){
	_subject = s;
	_subject->Attach(this);
}
AnalogClock::~AnalogClock(){
	_subject->Dettach(this);
}
void AnalogClock::Update(Subject* theChangedSubject){
	if (theChangedSubject == _subject){
		cout << "The AnalogClock Observer is Sucessfully Updated!!" << endl;
	}
}

int main()
{
	ClockTimer timer;
	DigitalClock dc(&timer);
	AnalogClock ac(&timer);

	timer.Tick();

	system("pause");
	return 0;
}