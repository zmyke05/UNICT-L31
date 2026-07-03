/*
Mutable is used to specify that the member does not affect the externally visible state of the class 
(as often used for mutexes, memo caches, lazy evaluation, and access instrumentation).
*/
struct Foo
{
	mutable int value;
	int secondvalue;
};

int main()
{
	const struct Foo foo = { 10, 100 };
	foo.value = 200;
	//foo.secondvalue = 100; error
}