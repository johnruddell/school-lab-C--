#ifndef TOKEN_H
#define TOKEN_H

#include <fstream>

using namespace std;

#include "WCS_Pointer.h"
#include "WCS_String.h"
#include "Operator.h"
#include "Variable.h"

class Token: public RefCount
	{
	public:
		//		**********	enums		**********
			enum	Variables				{
											NumVariables = 100
											};
			enum	Exception				{
											TokenFileNotOpen,
											BadTokenException

											};
			enum	TokenType				{
											EndOfInputToken,
											Unknown,
											VariableToken,
											ConstantToken,
											KeywordEvalToken,
											KeywordExpToken,
											KeywordValueToken,
											OperatorPlusToken,
											OperatorMinusToken,
											OperatorAsteriskToken,
											OperatorSlashToken,
											SymbolOpenParenToken,
											SymbolCloseParenToken,
											SymbolSemiColonToken,
											

											NumTokens
											};
		//		**********	typedefs	**********
			typedef unsigned char			UChar;
		//		**********	functions	**********
											Token			();
					explicit				Token			(const Token &);
					explicit				Token			(const WCS_Pointer<Token> &);
					explicit				Token			(TokenType, int);
											~Token			();
					Token &					Build			();
			static	void					CloseFile		();
			Operator::Precedence			GetPrecedence	() const;
					TokenType				GetType			() const;
					void					SetWhich		(int);
					void					SetType			(TokenType);
					Variable::ValueType		GetValue		() const;
					int						GetWhich		() const;
			static	void					OpenFile		(const WCS_String &);
					void					SetPrecedence	(Operator::Precedence);
					void					SetValue		(Variable::ValueType);
					Token &					operator=		(const Token &);
	private:
		//		**********	enums		**********
			enum	InputType				{
											InputUnknown,
											InputA,
											InputE,
											InputL,
											InputP,
											InputU,
											InputV,
											InputX,
											Input0,
											Input1,
											Input2,
											Input3,
											Input4,
											Input5,
											Input6,
											Input7,
											Input8,
											Input9,
											InputPlus,
											InputMinus,
											InputAsterisk,
											InputSlash,
											InputOpenParen,
											InputCloseParen,
											InputSemiColon,
											InputSpace,
											EndOfFile,

											NumInputs
											};
			enum	TokenState				{
											TokenComplete = -1,
											StartGettingToken,
											AfterE,				
											AfterV,
											AfterEX,
											AfterVA,
											AfterVAL,
											AfterVALU,
											AfterEV,
											AfterEVA,
											AfterVDigit,
											AfterCDigit,
											AfterCDigitDigit,
											NumStates
											};

		//		**********	typedefs	**********
			typedef int						State;
			typedef TokenState				(*TokenFunc)	(Token &);
		//	**********	functions	**********
			InputType				GetInputChar	();
			void					Init			(TokenType, int);
			void					PutBackLastChar	() const;
//			void					SetType			(TokenType);
//			void					SetWhich		(int);

			static	TokenState	BadToken (Token &);	// 0
			static	TokenState	UnknownToken (Token &); // 1
			static	TokenState	GotE (Token &); // 2
			static	TokenState	GotEX (Token &); // 3
			static	TokenState	GotEXP (Token &); // 4
			static	TokenState	GotV (Token &); // 5
			static	TokenState	GotVA (Token &); // 6
			static	TokenState	GotVAL (Token &); // 7
			static	TokenState	GotVALU (Token &); // 8
			static	TokenState	GotVALUE (Token &); // 9
			static	TokenState	GotEV (Token &); // 10
			static	TokenState	GotEVA (Token &); // 11
			static	TokenState	GotEVAL (Token &); // 12
			static	TokenState	PlusOp (Token &); // 13
			static	TokenState	MinusOp (Token &); // 14
			static	TokenState	AsteriskOp (Token &); // 15
			static	TokenState	SlashOp (Token &); // 16
			static  TokenState	OpenParenOp (Token &); // 17
			static  TokenState	CloseParenOp (Token &); // 18
			static  TokenState	SemiColonOp (Token &); // 19
			static	TokenState	Space (Token &); // 20
			static	TokenState	GotVDigit (Token &); // 21
			static	TokenState	GotVDigitDigit (Token &); // 22
			static	TokenState	GotCDigit (Token &); // 23
			static  TokenState	GotCDigitDigit (Token &); // 24
			static	TokenState	GotNonDigit (Token &); // 25
			static	TokenState	GotEndOfFile (Token &); // 26




			static	InputType				InputTable		[];
			static	UChar					LastChar;
			static	ifstream				SourceFile;
			static	TokenFunc				StateFunction	[];
			static	UChar					StateTable		[NumInputs] [NumStates];
			static	Variable				VariableArray	[NumVariables];
		//	**********	data		**********
					TokenType				Type;
					union
						{
						int						Which;
						Operator::Precedence	Precedence;
						Variable::ValueType		Value;
						} ;
	};

inline Token::Token ()
	{
	Init (EndOfInputToken, 0);
	}

inline Token::Token (const Token & T)
	{
	Init (T.Type, T.Which);
	}

inline Token::Token (const WCS_Pointer<Token> & T)
	{
	Init ((*T).Type, (*T).Which);
	}

inline Token::Token (TokenType NewType, int NewValue)
	{
	Init (NewType, NewValue);
	}

inline Token::~Token ()
	{
	}

inline void Token::CloseFile ()
	{
	SourceFile.close ();
	}

inline Operator::Precedence Token::GetPrecedence () const
	{
	return Precedence;
	}

inline Token::TokenType Token::GetType () const
	{
	return Type;
	}

inline Variable::ValueType Token::GetValue () const
	{
	return (Type == VariableToken) ? VariableArray [Which].GetValue () : Value;
	}

inline int Token::GetWhich () const
	{
	return Which;
	}

inline void Token::OpenFile (const WCS_String & FileName)
	{
//	if (FileName == "KEYBOARD")
//			SourceFile.attach (0);
//		else
			SourceFile.open (static_cast <const char *> (FileName));
	}

inline void Token::SetValue (Variable::ValueType V)
	{
	if (Type == VariableToken)
			VariableArray [Which].SetValue (V);
		else
			Value = V;
	}

inline Token & Token::operator= (const Token & T)
	{
	if (this != &T)
			Init (T.Type, T.Which);
		else;
	return *this;
	}

inline Token::InputType Token::GetInputChar ()
	{
	return InputTable [LastChar = static_cast <UChar> (SourceFile.get ())];
	}

inline void Token::Init (TokenType T, int V)
	{
	Type = T;
	Value = V;
	}

inline void Token::PutBackLastChar () const
	{
	SourceFile.putback (LastChar);
	}

inline void Token::SetPrecedence (Operator::Precedence P)
	{
	Precedence = P;
	}

inline void Token::SetType (TokenType T)
	{
	Type = T;
	}

inline void Token::SetWhich (int W)
	{
	Which = W;
	}

#endif
