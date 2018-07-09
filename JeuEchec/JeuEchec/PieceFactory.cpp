#include "PieceFactory.h"
#include "Pion.h"
#include "Tour.h"
#include "Chevalier.h"
#include "Fou.h"
#include "Reine.h"
#include "Roi.h"

PieceFactory::PieceFactory()
{
}


PieceFactory::~PieceFactory()
{
}

Piece * PieceFactory::CreatePiece(const Enums::EPieceType a_PieceType, const Enums::EPieceColor a_Color)
{
	switch (a_PieceType)
	{
	case Enums::EPieceType::Pion:
		return new Pion(a_Color, 2, 3);
		break;
	case Enums::EPieceType::Tour:
		return new Tour(a_Color, 4, 2, 1);
		break;
	case Enums::EPieceType::Chevalier:
		return new Chevalier(a_Color, 4, 4);
		break;
	case Enums::EPieceType::Fou:
		return new Fou(a_Color, 1, 5);
		break;
	case Enums::EPieceType::Reine:
		return new Reine(a_Color, 5, 3);
		break;
	case Enums::EPieceType::Roi:
		return new Roi(a_Color, 1, 0);
		break;
	default:
		break;
	}
	return nullptr;
}
