#include <iostream>
#include <tuple>

class ExpandWithConstructor
{
public:
	template <typename ... T>
	ExpandWithConstructor(T... args) { }
};

template <typename T>
int PrintArgs(T arg)
{
	std::cout<<arg<<", ";
	return 0;
}

template <typename Head, typename ... T>
class DebugPrinter : public DebugPrinter<T...>
{
public:
	DebugPrinter() { }

	template< typename ...Y>
	DebugPrinter(Y ... rest)
	{
		std::cout<<"Construction of: "<<"dioporco"<<" Values: ";
		ExpandWithConstructor{ PrintArgs(rest)... };
		std::cout<<std::endl;
	}

};

template <typename Head>
class DebugPrinter< Head >
{
public:
};

template <typename ... T>
class TypeContainer : public std::tuple<T...>
{
public:
	TypeContainer(T... args) :std::tuple<T...>(args...) {};
};

template <typename... T1> class CheckVariadic;

template <typename... T1, typename ...T2>
class CheckVariadic< TypeContainer<T1...>, TypeContainer<T2...>> :
	public DebugPrinter< T1, T2, T1...>...
{
public:
	CheckVariadic(T1... args1, T2... args2, T1... args3) : DebugPrinter< T1, T2, T1...>(args1, args2..., args1)... {}
};


template  <typename... nameParmsTypes, typename... constructorTypes>
struct svvard< TypeContainer<nameParmsTypes...>, TypeContainer<constructorTypes...> > : svard<nameParmsTypes, constructorTypes>...{
	svvard(nameParmsTypes... nameArgs_, constructorTypes... cArgs) : svard<nameParmsTypes, constructorTypes>(nameParms_, cParms_) {

	}
};


int main() {
	svvard< TypeContainer<int, char*>, TypeContainer<
	CheckVariadic< TypeContainer<int, float>, TypeContainer<char, void*>> checkVariadic1{ 1,2.2f,'c',(void*)0xddddd,5,6.6f, };
}