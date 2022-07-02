#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()


cMain::cMain(): wxFrame(nullptr, wxID_ANY, "GameDevIsKillingMe-MineSweeper",wxPoint(30,30),wxSize(800,700)) {
	btn = new wxButton * [mFieldWidth * mFieldHeight];
	wxGridSizer* grid = new wxGridSizer(mFieldWidth, mFieldHeight, 0, 0);

	mField = new int[mFieldWidth * mFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	for (int x = 0; x < mFieldWidth; x++) 
	{
		for (int y = 0; y < mFieldHeight; y++) 
		{
			btn[y * mFieldWidth + x] = new wxButton(this, 10000 + (y * mFieldWidth + x));
			btn[y * mFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * mFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * mFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, & cMain::OnButtonClicked, this);
			mField[y * mFieldWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain() {
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& _evt) {

	int x = (_evt.GetId() - 10000) % mFieldWidth;
	int y = (_evt.GetId() - 10000) / mFieldHeight;

	if (bFirstClick) {
		int mines = 30;

		while (mines) {
			int rx = rand() % mFieldWidth;
			int ry = rand() % mFieldHeight;

			if (mField[ry * mFieldWidth + rx] == 0 && rx != x && ry != y) {
				mField[ry * mFieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;
	}

	btn[y * mFieldWidth + x]->Enable(false);
	if (mField[y*mFieldWidth+x] == -1) {
		wxMessageBox("Bang!, u dead\nU suck son, game over");

		bFirstClick=true;

		for (int x = 0; x < mFieldWidth; x++)
		{
			for (int y = 0; y < mFieldHeight; y++) 
			{
				mField[y * mFieldWidth + x] = 0;
				btn[y * mFieldWidth + x]->SetLabel("");
				btn[y * mFieldWidth + x]->Enable(true);

			}
		}
	}
	else 
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++) 
		{
			for (int j = -1; j < 2; j++) 
			{
				if (x + i >= 0 && x + i < mFieldWidth && y + j >= 0 && y + j < mFieldHeight)
				{
					if (mField[(y + j) * mFieldWidth + (x + i)] == -1) {
						mine_count++;
					}
				}
			}
		}
		if (mine_count > 0) {
			btn[y * mFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}
	_evt.Skip();
}