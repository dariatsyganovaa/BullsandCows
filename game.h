#pragma once
namespace BullsandCows {
	void start_game();
	
	void generate_number(int* comp_number);

	bool input_user_number(int* user_number);
	void convert_number_to_mass(int number, int* mass);
	void check(int number);

	int calculate_bulls(int* comp_number, int* user_number);
	int calculate_cows(int* comp_number, int* user_number);
	 
	bool check_win(int bulls);
	void print_win_message();
}