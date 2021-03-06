/*****************************************************
* FILE NAME:	main.cpp							*
*                                                   *
* PURPOSE                                           *
* A project in C++ to apply automata theory			*
* knowledge for a college class named				*
* Discrete and Hybrid Systems (SIDIH).				*
* - Can remove non-accessible and non-coaccessible	*
*states.											*
* - Can convert NFAs to DFAs.						*
* - Support for synchronous and asynchronous		*
*product											*
* - DFA minimization.								*
*****************************************************/

#include "stdafx.h"
#include "automata.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iostream>


#define ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int readArrows(int& select, int& option_selected, std::vector<std::string> MENU_options)
{
	int c = 0;
	int arrow = 0;
	int flag = 1;
	c = 0;
	while (flag == 1)
	{
		switch ((c = _getch()))
		{
		case KEY_UP: //key up
		{
			if (select == 1)
			{
				select = MENU_options.size();
				system("cls");
				flag = 0;
				break;
			}
			select--;
			system("cls");
			flag = 0;
			break;
		}
		case KEY_DOWN: //key down
		{
			if (select == MENU_options.size())
			{
				select = 1;
				system("cls");
				flag = 0;
				break;
			}
			select++;
			system("cls");
			flag = 0;
			break;
		}
		case ENTER: //key up
		{
			option_selected = select;
			system("cls");
			flag = 0;
			break;
		}
		default:
			break;
		}
	}

	return arrow;
}

void subMENU(int& select, int& option_selected_sub, std::vector<Automato>& automatos, Automato& newautomato, std::vector<std::string>& automato_index, int& chosen_automato)
{
	switch (option_selected_sub)
	{
	case 1:
	{
		std::cout << "Automato: " << automato_index.at(chosen_automato) << std::endl;
		automatos.at(chosen_automato).printAutomato(std::cout);
		std::cout << "Press any key to return to main menu..." << std::endl;
		getchar();

		system("cls");
		option_selected_sub = 0;
		break;
	}
	case 2:
	{
		std::cout << "Automato: " << automato_index.at(chosen_automato) << std::endl;
		automatos.at(chosen_automato).printAutomato(std::cout);
		if (automatos.at(chosen_automato).checkAccessibility(1) == false)
		{
			system("cls");
			option_selected_sub = 0;
			break;
		}
		std::cout << "Press any key to return to main menu..." << std::endl;
		getchar();

		system("cls");
		option_selected_sub = 0;
		break;
	}
	case 3:
	{
		std::cout << "Automato: " << automato_index.at(chosen_automato) << std::endl;
		automatos.at(chosen_automato).printAutomato(std::cout);
		if (automatos.at(chosen_automato).checkCoAccessibility(1) == false)
		{
			system("cls");
			option_selected_sub = 0;
			break;
		}
		std::cout << "Press any key to return to main menu..." << std::endl;
		getchar();

		system("cls");
		option_selected_sub = 0;
		break;
	}
	case 4:
	{
		automatos.at(chosen_automato).checkDFANFA(0);
		automatos.at(chosen_automato).checkAccessibility(0);
		automatos.at(chosen_automato).checkCoAccessibility(0);
		automatos.at(chosen_automato).printAutomato(std::cout);

		std::cout << "Trimed automato:" << automato_index.at(chosen_automato) << std::endl;
		std::cout << "Press any key to return to main menu..." << std::endl;

		getchar();

		system("cls");
		option_selected_sub = 0;
		break;
	}
	case 5:
	{
		std::cout << "Automato: " << automato_index.at(chosen_automato) << std::endl;
		automatos.at(chosen_automato).printAutomato(std::cout);
		if (automatos.at(chosen_automato).checkDFANFA(1) == false)
		{
			system("cls");
			option_selected_sub = 0;
			break;

		}
		std::cout << "Press any key to return to main menu..." << std::endl;
		getchar();

		system("cls");
		option_selected_sub = 0;
		break;
	}
	case 6:
	{
		std::cout << "Automato: " << automato_index.at(chosen_automato) << std::endl;
		if (automatos.at(chosen_automato).minimizationDFA() == true)
		{
			system("cls");
			std::cout << "Automato: " << automato_index.at(chosen_automato) << std::endl;
			automatos.at(chosen_automato).printAutomato(std::cout);
		}

		std::cout << "Press any key to return to main menu..." << std::endl;
		getchar();
		system("cls");
		option_selected_sub = 0;
		break;
	}
	case 7:
	{
		Automato productautomato;

		if (automato_index.size() <= 1)
		{
			std::string temp;
			std::cout << "Warning: Only one automato in memory! Use <Load automato> option to load a file." << std::endl;
			std::cout << "Do you wish to continue? (y/n)" << std::endl;
			std::cin >> temp;
			getchar();
			system("cls");
			if (temp == "no" || temp == "n" || temp == "NO" || temp == "N")
			{
				system("cls");
				select = 1;
				option_selected_sub = 0;
				break;
			}
		}
		int option_selected_sub_temp = option_selected_sub;

		int chosen_automato_A = chosen_automato;
		int chosen_automato_B = 0;
		int select_temp = select;
		int flag = 1;
		option_selected_sub = 0;
		select = 1;
		while (flag == 1)
		{
			std::cout << "Sync product " << std::endl;
			std::cout << "Automato A: " << automato_index.at(chosen_automato_A) << std::endl;
			std::cout << "Automato B: " << std::endl;
			for (auto i = 0; i != automato_index.size(); i++)
			{
				if (i + 1 == select)
				{
					std::cout << "->";
				}
				else
				{
					std::cout << "  ";
				}
				std::cout << automato_index.at(i) << std::endl;
			}
			readArrows(select, option_selected_sub, automato_index);
			if (option_selected_sub != 0)
				break;
		}
		system("cls");
		chosen_automato_B = (option_selected_sub - 1);

		std::cout << "Sync product " << std::endl;
		std::cout << "Automato A: " << automato_index.at(chosen_automato_A) << std::endl;
		std::cout << "Chose automato B: " << automato_index.at(chosen_automato_B) << std::endl;

		std::string temp_index = "SyncProduct_" + automato_index.at(chosen_automato_A) + "_" + automato_index.at(chosen_automato_B);
		if (find(automato_index.begin(), automato_index.end(), temp_index) == automato_index.end()) /* Check if automato is already in memory */
		{
			automato_index.push_back(temp_index);
			productautomato.automato_Path = temp_index;
			productautomato.productDFAteste(chosen_automato_A, chosen_automato_B, automatos);
			automatos.push_back(productautomato);

			std::cout << "Press any key to return to main menu..." << std::endl;
			getchar();
			system("cls");
			select = select_temp;
			option_selected_sub = 0;
			break;
		}
		else
		{
			std::cout << "This Sync product is already in memory!" << std::endl;
			std::cout << "Press any key to return to main menu..." << std::endl;

			getchar();
			system("cls");
			select = select_temp;
			option_selected_sub = 0;
			break;
		}
	}
	case 8:
	{
		Automato parallelautomato;

		if (automato_index.size() <= 1)
		{
			std::string temp;
			std::cout << "Warning: Only one automato in memory! Use <Load automato> option to load a file." << std::endl;
			std::cout << "Do you wish to continue? (y/n)" << std::endl;
			std::cin >> temp;
			getchar();
			system("cls");
			if (temp == "no" || temp == "n" || temp == "NO" || temp == "N")
			{
				system("cls");
				select = 1;
				option_selected_sub = 0;
				break;
			}
		}
		int option_selected_sub_temp = option_selected_sub;

		int chosen_automato_A = chosen_automato;
		int chosen_automato_B = 0;
		int select_temp = select;
		int flag = 1;
		option_selected_sub = 0;
		select = 1;
		while (flag == 1)
		{
			std::cout << "Async product " << std::endl;
			std::cout << "Automato A: " << automato_index.at(chosen_automato_A) << std::endl;
			std::cout << "Automato B: " << std::endl;
			for (auto i = 0; i != automato_index.size(); i++)
			{
				if (i + 1 == select)
				{
					std::cout << "->";
				}
				else
				{
					std::cout << "  ";
				}
				std::cout << automato_index.at(i) << std::endl;
			}
			readArrows(select, option_selected_sub, automato_index);
			if (option_selected_sub != 0)
				break;
		}
		system("cls");
		chosen_automato_B = (option_selected_sub - 1);

		std::cout << "Async product " << std::endl;
		std::cout << "Automato A: " << automato_index.at(chosen_automato_A) << std::endl;
		std::cout << "Chose automato B: " << automato_index.at(chosen_automato_B) << std::endl;

		std::string temp_index = "AsyncProduct_" + automato_index.at(chosen_automato_A) + "_" + automato_index.at(chosen_automato_B);

		if (find(automato_index.begin(), automato_index.end(), temp_index) == automato_index.end()) /* Check if automato is already in memory */
		{
			automato_index.push_back(temp_index);
			parallelautomato.automato_Path = temp_index;
			parallelautomato.parallelDFAteste(chosen_automato_A, chosen_automato_B, automatos);
			automatos.push_back(parallelautomato);

			std::cout << "Press any key to return to main menu..." << std::endl;
			getchar();
			system("cls");
			select = select_temp;
			option_selected_sub = 0;
			break;
		}
		else
		{
			std::cout << "This Async product is already in memory!" << std::endl;
			std::cout << "Press any key to return to main menu..." << std::endl;

			getchar();
			system("cls");
			select = select_temp;
			option_selected_sub = 0;
			break;
		}
	}
	break;
	case 9:
		break;
	default:
		break;
	}
}

void Menu()
{
	std::vector<std::string> MENU_options{
		"Load automato",
		"Choose automato",
		"Operations",
		"Rename automato",
		"Delete automato",
		"Save automato to File",
		"About",
		"Exit"
	};
	std::vector<std::string> Sub_MENU_options{
		"Display automato",
		"Check automato accesibility",
		"Check automato coaccesibility",
		"Trim",
		"Check if the automato is DFA or NFA",
		"Minimize automato",
		"Compute sync product",
		"Compute async product",
		"Return to main menu",
	};

	std::vector<Automato> automatos;
	Automato newautomato;
	std::vector<std::string> automato_index;
	int chosen_automato = 0, select = 1, option_selected = 0, exit = 0;

	while (exit == 0)
	{
		for (int i = 0; i != MENU_options.size(); i++)
		{
			if (i + 1 == select)
				std::cout << "->";
			else
				std::cout << "  ";

			std::cout << MENU_options.at(i) << std::endl;
		}

		readArrows(select, option_selected, MENU_options);

		switch (option_selected)
		{
		case 1:
		{
			std::string Path;
			system("cls");

			std::cout << "Choose path for file: " << std::endl;
			std::cin >> Path;
			getchar();
			system("cls");
			std::ifstream myfile(Path);

			if (myfile.is_open())
			{
			
				if (find(automato_index.begin(), automato_index.end(), Path) == automato_index.end()) /* Check if automato is already in memory */
				{
					automato_index.push_back(Path);
					newautomato.automato_Path = Path;
					if (newautomato.loadFile(Path.c_str()) == true)
					{
						auto m = find(automato_index.begin(), automato_index.end(), Path);
						automatos.push_back(newautomato);
						chosen_automato = (m - automato_index.begin());

						std::cout << "Press any key to return to main menu..." << std::endl;
						getchar();

						system("cls");
						option_selected = 0;
						break;
					}
				}
				else
				{
					std::cout << "This automato is already in memory!" << std::endl;
					std::cout << "Press any key to return to main menu..." << std::endl;

					getchar();

					system("cls");
					option_selected = 0;
					break;
				}
			}
			else
			{
				std::cout << "Unable to find file, Check file location!" << std::endl;
				std::cout << "Press any key to return to main menu..." << std::endl;

				getchar();

				system("cls");
				option_selected = 0;
				break;
			}
			break;
		}
		case 2:
		{
			int temp_select = select;
			if (automato_index.empty() == true)
			{
				std::cout << "No automato in memory! Use <Load automato> option to load a file." << std::endl;
				std::cout << "Press any key to return to main menu..." << std::endl;
				getchar();
				system("cls");
				select = temp_select;
				option_selected = 0;
				break;
			}

			select = 1;
			int option_selected_sub = 0;
			while (1)
			{
				for (int i = 0; i != MENU_options.size(); i++)
				{
					if (i == option_selected - 1)
					{
						std::cout << "  " << MENU_options.at(i) << ": " << std::endl;
						i++;

						for (int j = 0; j != automato_index.size(); j++)
						{
							if (j + 1 == select)
								std::cout << "  ->";

							else
								std::cout << "    ";

							std::cout << automato_index.at(j) << std::endl;
						}
					}
					std::cout << "  " << MENU_options.at(i) << std::endl;
				}
				readArrows(select, option_selected_sub, automato_index);
				chosen_automato = (option_selected_sub - 1);
				if (option_selected_sub != 0)
					break;
			}
			system("cls");
			select = temp_select;
			option_selected = 0;

			break;
		}
		case 3:
		{
			int temp_select = select;
			if (automato_index.empty() == true)
			{
				std::cout << "No automato in memory! Use <Load automato> option to load a file." << std::endl;
				std::cout << "Press any key to return to main menu..." << std::endl;
				getchar();
				system("cls");
				select = temp_select;
				option_selected = 0;
				break;
			}

			select = 1;
			int option_selected_sub = 0;
			while (1)
			{
				for (int i = 0; i != MENU_options.size(); i++)
				{
					if (i == option_selected - 1)
					{
						std::cout << "  " << MENU_options.at(i) << ": " << automato_index.at(chosen_automato) << std::endl;
						i++;

						for (int j = 0; j != Sub_MENU_options.size(); j++)
						{
							if (j + 1 == select)
								std::cout << "  ->";

							else
								std::cout << "    ";

							std::cout << Sub_MENU_options.at(j) << std::endl;
						}
					}
					std::cout << "  " << MENU_options.at(i) << std::endl;
				}

				readArrows(select, option_selected_sub, Sub_MENU_options);
				if (option_selected_sub == 9)
					break;
				subMENU(select, option_selected_sub, automatos, newautomato, automato_index, chosen_automato);
			}
			system("cls");
			select = temp_select;
			option_selected = 0;

			break;
		}

		case 4:
		{
			int temp_select = select;
			if (automato_index.empty() == true)
			{
				std::cout << "No automato in memory! Use <Load automato> option to load a file." << std::endl;
				std::cout << "Press any key to return to main menu..." << std::endl;
				getchar();
				system("cls");
				select = temp_select;
				option_selected = 0;
				break;
			}

			select = 1;
			int option_selected_sub = 0;
			while (1)
			{
				for (int i = 0; i != MENU_options.size(); i++)
				{
					if (i == option_selected - 1)
					{
						std::cout << "  " << MENU_options.at(i) << ": " << std::endl;
						i++;

						for (int j = 0; j != automato_index.size(); j++)
						{
							if (j + 1 == select)
								std::cout << "  ->";

							else
								std::cout << "    ";

							std::cout << automato_index.at(j) << std::endl;
						}
					}
					std::cout << "  " << MENU_options.at(i) << std::endl;
				}
				readArrows(select, option_selected_sub, automato_index);


				if (option_selected_sub == select)
				{
					std::string temp_path;
					system("cls");

					std::cout << "Choose new name for file: " << std::endl;
					std::cin >> temp_path;
					getchar();
					automatos.at((option_selected_sub - 1)).automato_Path = std::string{};
					automatos.at((option_selected_sub - 1)).automato_Path = temp_path;

					automato_index.erase(automato_index.begin() + (option_selected_sub - 1));
					automato_index.insert(automato_index.begin() + (option_selected_sub - 1), temp_path);

					option_selected_sub = 0;
					select = 1;
					break;
				}

			}
			system("cls");
			select = temp_select;
			option_selected = 0;

			break;
		}
		case 5:
		{
			int temp_select = select;
			if (automato_index.empty() == true)
			{
				std::cout << "No automato in memory! Use <Load automato> option to load a file." << std::endl;
				std::cout << "Press any key to return to main menu..." << std::endl;
				getchar();
				system("cls");
				select = temp_select;
				option_selected = 0;
				break;
			}

			select = 1;
			int option_selected_sub = 0;
			while (1)
			{
				for (int i = 0; i != MENU_options.size(); i++)
				{
					if (i == option_selected - 1)
					{
						std::cout << "  " << MENU_options.at(i) << ": " << std::endl;
						i++;

						for (int j = 0; j != automato_index.size(); j++)
						{
							if (j + 1 == select)
								std::cout << "  ->";

							else
								std::cout << "    ";

							std::cout << automato_index.at(j) << std::endl;
						}
					}
					std::cout << "  " << MENU_options.at(i) << std::endl;
				}
				readArrows(select, option_selected_sub, automato_index);


				if (option_selected_sub == select)
				{
					automato_index.erase(automato_index.begin() + (option_selected_sub - 1));
					automatos.erase(automatos.begin() + (option_selected_sub - 1));
					option_selected_sub = 0;
					select = 1;
					break;
				}

			}
			system("cls");
			select = temp_select;
			option_selected = 0;

			break;
		}
		case 6:
		{
			int temp_select = select;
			if (automato_index.empty() == true)
			{
				std::cout << "No automato in memory! Use <Load automato> option to load a file." << std::endl;
				std::cout << "Press any key to return to main menu..." << std::endl;
				getchar();
				system("cls");
				select = temp_select;
				option_selected = 0;
				break;
			}

			select = 1;
			int option_selected_sub = 0;
			while (1)
			{
				for (int i = 0; i != MENU_options.size(); i++)
				{
					if (i == option_selected - 1)
					{
						std::cout << "  " << MENU_options.at(i) << ": " << std::endl;
						i++;

						for (int j = 0; j != automato_index.size(); j++)
						{
							if (j + 1 == select)
								std::cout << "  ->";

							else
								std::cout << "    ";

							std::cout << automato_index.at(j) << std::endl;
						}
					}
					std::cout << "  " << MENU_options.at(i) << std::endl;
				}
				readArrows(select, option_selected_sub, automato_index);


				if (option_selected_sub == select)
				{
					std::string Path;
					system("cls");

					std::cout << "Choose the path for file: " << std::endl;
					std::cin >> Path;
					getchar();

					automatos.at((option_selected_sub - 1)).saveToFile(Path);

					option_selected_sub = 0;
					select = temp_select;
					break;
				}

			}
			system("cls");
			select = temp_select;
			option_selected = 0;

			break;
		}
		case 7:
		{
			std::cout << "SIDIH - Sistemas Discretos e Hibridos" << std::endl;
			std::cout << "JOAO RESENDE (1140569)" << std::endl;
			std::cout << "Press any key to return to main menu..." << std::endl;
			getchar();
			system("cls");

			option_selected = 0;
			break;
		}
		case 8:
		{
			exit = 1;
			break;
		}
		default:
			break;
		}
	}
}


int main()
{
	Menu();
	
	return 0;
}

