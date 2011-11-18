#include <iostream>
#include "MathTree.h"

MathTree::Node::Node (const Token & T): Token (T)
	{
	}

MathTree::Node::~Node ()
	{
	}

MathTree::MathTree ()
	{
	}

MathTree::~MathTree ()
	{
	}

void MathTree::InsertBinaryOperator (const Token & T)
	{
	WCS_Pointer <Node>	pNode (new Node (T));

	while ((pLastOperator.Exists ()) && ((*pLastOperator).GetPrecedence () >= (*pNode).GetPrecedence ()))
		pLastOperator = (*pLastOperator).pParent;

	if (pLastOperator.DoesNotExist ())
		{
		(*pRoot).pParent	= pNode;
		(*pNode).pLeft		= pRoot;
		pRoot				= pNode;
		}
	else
		{
		(*pNode).pLeft				= (*pLastOperator).pRight;
		(*(*pNode).pLeft).pParent	= pNode;
		(*pLastOperator).pRight		= pNode;
		(*pNode).pParent			= pLastOperator;
		}
	pLastOperator = pNode;
	}

void MathTree::InsertOperand (const Token & T)
	{
	WCS_Pointer <Node>	pNode (new Node (T));

	if (pRoot.DoesNotExist ())
		pRoot = pNode;
	else
		{
		(*pLastOperator).pRight = pNode;
		(*pNode).pParent		= pLastOperator;
		}
	}

void MathTree::InsertUnaryOperator (const Token & T)
	{
	Token Temp (Token::ConstantToken, 0);

	InsertOperand (Temp);
	InsertBinaryOperator (T);
	}

//WCS_Pointer <MathTree::Node> & MathTree::GetLeftMostOperator (WCS_Pointer <Node> pNode)
//{
//	WCS_Pointer <Node> pTemp;
//	if (pNode.Exists ())
//	{
//		while((*pNode).pLeft.Exists ())
//		{
//			(*pNode).IsLeftSideDone	= false;
//			pNode					= (*pNode).pLeft;
//		}
//		pNode = (*pNode).pParent;
//		//return (*pNode).pParent;
//	}
//	return pNode;
//}

WCS_Pointer <MathTree::Node> & MathTree::GetLeftMostOperator (WCS_Pointer <Node> & pNode)
	{
	WCS_Pointer <Node> pTemp;
	if (pNode.Exists ())
		{
		pTemp = GetLeftMost(pNode);
		//pNode = (*pNode).pParent;
		return (*pTemp).pParent;
		}
	return pNode;
	}

WCS_Pointer <MathTree::Node> & MathTree::GetLeftMost (WCS_Pointer <Node> & pNode)
	{
	if((*pNode).pLeft.Exists ()){
		(*pNode).IsLeftSideDone = false;
		return GetLeftMost((*pNode).pLeft);
		}
	else
		return pNode;
	}



Variable::ValueType MathTree::Evaluate ()
	{
	if (pRoot.Exists ())
		{
		WCS_Pointer <Node> pNode;

		pNode = GetLeftMostOperator (pRoot);
		while (pNode.Exists ())
			if (!(*pNode).IsLeftSideDone)
				{
				(*pNode).SetValue ((*(*pNode).pLeft).GetValue ());
				(*pNode).IsLeftSideDone	= true;
				pNode = GetLeftMostOperator ((*pNode).pRight);
				}
			else
				{
				switch ((*pNode).GetType ())
					{
				case Token::OperatorPlusToken:
					(*pNode).SetValue ((*pNode).GetValue () + (*(*pNode).pRight).GetValue ());
					break;
				case Token::OperatorMinusToken:
					(*pNode).SetValue ((*pNode).GetValue () - (*(*pNode).pRight).GetValue ());
					break;
				case Token::OperatorSlashToken:
					if ((*(*pNode).pRight).GetValue () == 0)
						throw DivideByZero;
					else
						(*pNode).SetValue ((*pNode).GetValue () / (*(*pNode).pRight).GetValue ());
					break;
				case Token::OperatorAsteriskToken:
					(*pNode).SetValue ((*pNode).GetValue () * (*(*pNode).pRight).GetValue ());
					break;
					}
				pNode = (*pNode).pParent;
				}
			return (*pRoot).GetValue ();
		}
	else
		return 0;
	}
void MathTree::Delete ()
	{
	pLastOperator.SetToNull();
	WCS_Pointer <Node> FromWhere = pRoot;
	WCS_Pointer <Node> pDelete = pRoot;
	bool IsRightSideDeleted = false;
	bool IsLeftSideDeleted = false;
	if (pRoot.Exists()){
		while (IsLeftSideDeleted != true && IsRightSideDeleted != true){

			while (IsRightSideDeleted == false){

				while (IsLeftSideDeleted == false){
					pDelete = GetLeftMostOperator (FromWhere);
					cout<<" Just arrived at the leftmost operator.. which is " << (*FromWhere).GetType()<< " Containing the value " << (*FromWhere).GetValue()<<endl;

					while (pDelete != pRoot){
						cout<< "The operator's enumeration value is: "<< (*pDelete).GetType()<<endl;
						cout<<"The Left node's enumeration value is: "<< (*(*pDelete).pLeft).GetType()<<endl;
						cout<<"The Right node's enumeration value is: "<< (*(*pDelete).pRight).GetType()<<endl;

						//((*(*pDelete).pLeft).pParent).SetToNull();
						((*pDelete).pLeft).SetToNull();

						while ((*(*pDelete).pRight).pLeft != NULL && (*pDelete).pRight != NULL){
							pDelete = (*(*pDelete).pRight).pLeft;

							cout<< "The operator's enumeration value is: "<< (*pDelete).GetType()<<endl;
							cout<<"The Left node's enumeration value is: "<< (*(*pDelete).pLeft).GetType()<<endl;
							cout<<"The Right node's enumeration value is: "<< (*(*pDelete).pRight).GetType()<<endl;
							}
						if ((*pDelete).pLeft.Exists())
							{
							cout<<"The Left node's enumeration value is: "<< (*(*pDelete).pLeft).GetType()<<endl;
							//((*(*pDelete).pLeft).pParent).SetToNull();
							
							((*pDelete).pLeft).SetToNull();
							}
						cout<<"The Right node's enumeration value is: "<< (*(*pDelete).pRight).GetType()<<endl;
						
						//((*(*pDelete).pRight).pParent).SetToNull();
						((*pDelete).pRight).SetToNull();
						pDelete = (*pDelete).pParent;

						}
					IsLeftSideDeleted = true;
					FromWhere = (*pRoot).pRight;
					cout<<"Done Deleting the left side, now moving on to the right side " <<endl;

					}
				IsRightSideDeleted = true;
				cout<<"Done Deleting the Right side, now just have to delete the root " <<endl;
				}
			}
		cout<<"The Root's enumeration value is: "<< (*pRoot).GetType()<<" containing the value: " <<(*pRoot).GetValue()<<endl;
		pRoot.SetToNull();
		cout<<"Your Tree Has Been Deleted! Either start over with a new tree or press X to exit "<<endl;
		}
	}
void MathTree::walkingPrint()
{
    
    bool isLeftSidePrinted = false;
    bool isRightSidePrinted = false;
    WCS_Pointer<Node> pIterator = pRoot;
    WCS_Pointer<Node> pLocation = pIterator;
    WCS_Pointer<Node> fromWhere = pRoot;
    int x=5,y=5;
    setEmptyGrid();
    
    if (pRoot.Exists()) {
        while (isRightSidePrinted != true && isRightSidePrinted != true) {
            while (isLeftSidePrinted != true) {
                while (isLeftSidePrinted != true) {
                    pIterator = GetLeftMostOperator(fromWhere);
                    while (pIterator != pRoot) {
                        x+=x,y+=y;
  //                      pLocation = pIterator;
 //                       print [x][y] = pLocation;
                        if ((*pIterator).pLeft.Exists()) {
                            print [--x][--y] = (*(*pIterator).pLeft).GetValue();
                            x++,y++;
                        }
                        if ((*pIterator).pRight.Exists()) {
                            print[++x][--y] = (*(*pIterator).pRight).GetValue();
                            x--,y++;
                        }
                        
//                        PrintTree(pIterator);
                        
                        while ((*(*pIterator).pRight).pLeft != NULL && (*pIterator).pRight != NULL) {
                            pIterator = (*(*pIterator).pRight).pLeft;
                        }
                            if ((*pIterator).pLeft.Exists()) {
//                                print [x][y] = pLocation;
                                print[--x][--y] = (*(*pIterator).pLeft).GetValue();
                                x++,y++;
                            }
//                            print [x][y] = pLocation;
                        if ((*pIterator).pRight.Exists()) {
                            print[++x][--y] = (*(*pIterator).pRight).GetValue();
                            x--,y++;
  //                          PrintTree(print);
                            pIterator = (*pIterator).pParent;
                        
                    }
                    isLeftSidePrinted = true;
                    pIterator = (*pRoot).pLeft;
                
                }
                isRightSidePrinted = true;
            }
        }
        PrintTree(print);
    }
    
}
}

void MathTree::PrintTree(Variable::ValueType print [][100])
{
    for (int i = 0; i<=100;i++){
        for (int j=0;j<=100;j++){
            cout << print [i] [j];
            //            cout<< print [i][j];
        }
    }
}

Variable::ValueType  MathTree::setEmptyGrid()
{
    for (int i = 0; i<=100;i++){
        for (int j=0;j<=100;j++){
            print [i] [j] = ' ';
//            cout<< print [i][j];
        }
    }
}
