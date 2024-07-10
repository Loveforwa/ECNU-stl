#ifndef RecordType
#define RecordType
#include "iostream"
using namespace std;
class Record{
public:
	Record(int x=0, int y=0);
	int the_key() const;
private:
	int key;
	int other;
};
bool operator == (const Record &x, const Record &y);
bool operator > (const Record &x, const Record &y);
bool operator < (const Record &x, const Record &y);
bool operator <= (const Record &x, const Record &y);
ostream & operator << (ostream &output, Record &x);

Record::Record(int x, int y){
	key=x;
	other=y;
}
int Record::the_key() const{
	return key;
}
bool operator == (const Record &x, const Record &y)
{
	return x.the_key( ) == y.the_key( );
}
bool operator > (const Record &x, const Record &y)
{
	return x.the_key( ) > y.the_key( );
}
bool operator < (const Record &x, const Record &y)
{
	return x.the_key( ) < y.the_key( );
}
bool operator <= (const Record &x, const Record &y)
{
	return x.the_key( ) <= y.the_key( );
}
ostream & operator << (ostream &output, Record &x)
{
	output<<x.the_key();
	output<<"  ";
	return output;
}
#endif