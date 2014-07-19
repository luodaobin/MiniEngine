#include <iostream>
namespace AA
{
enum EKinds
{
		EKinds_A,
		EKinds_B,
		EKinds_C,
};
}

void main()
{
     std::cout<<typeid(AA::EKinds).name()<<std::endl;
	 std::cout<<typeid(AA::EKinds_A).name()<<std::endl;
	 std::cout<<typeid(AA::EKinds_B).name()<<std::endl;

}
