#ifndef MATH_TREE_H
#define MATH_TREE_H

#include "WCS_Pointer.h"

#include "Token.h"

class MathTree
{
private:
	class Node: public Token	// Token is derived from RefCount so Node will work with WCS_Pointer
	{
	public:
		Node	(const Token &);
		~Node	();
		Node	();
		Node	(const Node &);
		void	operator =	(const Node &);

		WCS_Pointer <Node>		pParent;
		WCS_Pointer <Node>		pLeft;
		WCS_Pointer <Node>		pRight;
		bool					IsLeftSideDone;

	};
public:
	enum	Exceptions	{DivideByZero};
	MathTree ();
	~MathTree ();
	WCS_Pointer <Node> & GetLeftMostOperator (WCS_Pointer <Node> &);
	WCS_Pointer <Node> & GetLeftMost (WCS_Pointer <Node> &);
	Variable::ValueType Evaluate ();
	void Delete ();
	void InsertBinaryOperator (const Token &);
	void InsertOperand (const Token &);
	void InsertUnaryOperator (const Token &);
    void walkingPrint ();
    void PrintTree(Variable::ValueType [][100]);
    Variable::ValueType setEmptyGrid ();
    Variable::ValueType print [100][100];
private:
	MathTree (const MathTree &);
	void operator = (const MathTree &);
   // WCS_Pointer <Node> grid [400] [400];
     


	WCS_Pointer <Node>	pRoot;
	WCS_Pointer <Node>	pLastOperator;
};

#endif
