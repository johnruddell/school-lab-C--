#include <iostream>
#include "MathTree.h"
#include "Token.h"

using namespace std;

int main (int argc, char * argv [])
	{
	WCS_String temp;
	char op;
	char character;
	long i;
	long val;
	MathTree mathTree;
	Token token;

	cout<<"********************** Welcome to the MathTree Calculator!! ********************" << endl;
	cout<<"Enter 'C' followed by a whole number to enter a constant in the tree" <<endl;
	cout<<"Enter 'V' followed by two digits to enter a variable into the tree" <<endl;
	cout<<"Enter 'v' followed by two digits, a space, and then up to three digits"<<endl;
	cout<<"To set a value to your variable" <<endl;
	cout<<"Enter 'O' followed by and operator (+ - * /) followed by a digit "<<endl;
	cout<<"To insert an operator into the tree with a percedence set by the digit"<<endl;
	cout<<"Enter 'E' to evaluate the tree and to see what the answer is" <<endl;
	cout<<"Enter 'D' to delete the tree" <<endl;
	cout<<"Enter 'X' to exit the program"<<endl;
	cout<<endl;
	cout<<"\t\t\t    ENTER A VALID IMPUT " <<endl;
	for(;;)
		{
		character = cin.get();
		switch (character)
			{
		case 'c':
		case 'C':
			cin >> i;
			cin.ignore ();
			cout<<"you entered a constant "<< i << endl;
			cout<<"\n"<<endl;
			token.SetType (Token::ConstantToken);	// move SetType from private to public in tokenn class
			token.SetValue (i);
			mathTree.InsertOperand (token);
			break;
		case 'V':
			cin >> i;
			cin.ignore ();
			cout<<"You want to enter the variable " << i <<endl;
			token.SetType (Token::VariableToken);
			token.SetWhich (i);
			mathTree.InsertOperand (token);
			cout<<"You entered the variable "<<token.GetWhich() <<endl;
			cout<<"\n"<<endl;
			break;
		case 'e':
		case 'E':
			try{
				cout << "Answer is " << mathTree.Evaluate () << endl;
				cout<<"\n"<<endl;
				}
			catch(MathTree::Exceptions E){
				switch (E){
				case 0:
					cout<<"cannot divide by 0 exiting program.. "<< endl;
					exit (0);
					}
			}
		break;
		case 'v':
			cin >> i;
			cin >> val;
			cin.ignore ();
			cout<<"You want to set the variable " << i << " To the value " << val <<endl;
			token.SetType (Token::VariableToken);
			token.SetWhich (i);
			token.SetValue (val);
			cout<<"the variables value is "<<token.GetValue()<<endl;
			cout<<"\n"<<endl;
			break;
		case 'X':
		case 'x':
			exit (0);
			break;
		case 'O':
		case 'o':
			cin >> op;
			cin >> val;
			cin.ignore ();
			cout<<"You Entered a " << op << " Operator " << endl;
			cout<<"You want to set the " << op << " Operator's precedence to " << val << endl;
			if (op == '+'){
				token.SetType(Token::OperatorPlusToken);
				token.SetPrecedence((Operator::Precedence)(val));
				mathTree.InsertBinaryOperator (token);
				cout<<"operators precedence is : " << token.GetPrecedence() << endl;
				cout<<"\n"<<endl;
				}
			else
				if (op =='-'){
					token.SetType(Token::OperatorMinusToken);
					token.SetPrecedence((Operator::Precedence)(val));
					mathTree.InsertBinaryOperator (token);
					cout<<"operators precedence is : " << token.GetPrecedence() << endl;
					cout<<"\n"<<endl;
					}
				else 
					if (op == '*'){
						token.SetType(Token::OperatorAsteriskToken);
						token.SetPrecedence((Operator::Precedence)(val));
						mathTree.InsertBinaryOperator (token);
						cout<<"operators precedence is : " << token.GetPrecedence() << endl;
						cout<<"\n"<<endl;
						}
					else
						if (op == '/'){
							token.SetType(Token::OperatorSlashToken);
							token.SetPrecedence((Operator::Precedence)(val));
							mathTree.InsertBinaryOperator (token);
							cout<<"operators precedence is : " << token.GetPrecedence() << endl;
							cout<<"\n"<<endl;
							}
						break;

		case 'd':
		case 'D':
			cout<< "Deleting the tree " << endl;
			cout<<"Keep in mind that.... "<< endl;
			cout<<" Variable Token's Enumeration value is 2"<<endl;
			cout<<" Constant Token's Enumeration value is 3"<<endl;
			cout<<" BinaryPlus Token's Enumeration value is 7"<<endl;
			cout<<" BinaryMinus Token's Enumeration value is 8"<<endl;
			cout<<" BinaryAsterisk Token's Enumeration value is 9"<<endl;
			cout<<" BinarySlash Token's Enumeration value is 10"<<endl;
			mathTree.Delete();	
                    break;
        case 'P':
        case 'p':
                    cout<<"Printing your Tree " <<endl;
                    mathTree.walkingPrint();

		}	
	}
        return 0;
	}
