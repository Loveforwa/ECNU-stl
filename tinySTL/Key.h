class Key {
	int key;
public:
	Key (int x = 0);
	int the_key( ) const;
};

bool operator == (const Key &x, const Key &y);
bool operator < (const Key &x, const Key &y);
bool operator > (const Key &x, const Key &y);

Key::Key(int x){
	key=x;
}

int Key::the_key() const{

	return key;

}

bool operator == (const Key &x, const Key &y)
{
	return x.the_key( ) == y.the_key( );
}

bool operator > (const Key &x, const Key &y)
{
	return x.the_key( ) > y.the_key( );
}

bool operator < (const Key &x, const Key &y)
{
	return x.the_key( ) < y.the_key( );
}