#include <iostream>
#include <exception>
#include <stdexcept>
#include <ctime>
#include <clocale>
#include "game.h"

void BullsandCows::start_game() {
	setlocale(LC_ALL, "rus");
	int* comp_number = (int*)malloc(sizeof(int) * 4);
	int* user_number = (int*)malloc(sizeof(int) * 4);
	generate_number(comp_number);
	std::cout << "Я загадал четырёхзначное число без повторения цифр. Попробуй его угадать! " << std::endl;
	while (1) {
		int cows = 0, bulls = 0;

		if (input_user_number(user_number) == false) {
			continue;
		}

		bulls = calculate_bulls(comp_number, user_number);
		cows = calculate_cows(comp_number, user_number);

		std::cout << "Количество быков: " << bulls << " , " << "количество коров: " << cows << std::endl;
		std::cout << std::endl; 

		if (check_win(bulls)) {
			print_win_message();
			break;
		}
	}
}
void BullsandCows::generate_number(int* comp_number) {
	bool numbers_used[10] = { false };
	srand(time(NULL));

	int first_digit;

	do {
		first_digit = rand() % 10;
	} while (first_digit == 0);

	comp_number[0] = first_digit;
	numbers_used[first_digit] = true;

	int digit;
	for (int i = 0; i < 4; i++) {

		do {
			digit = rand() % 10; 
		} while (numbers_used[digit] == true);

		comp_number[i] = digit;
		numbers_used[digit] = true;
	}
	
	/*std::cout << "Сгенерированное число: ";
	for (int i = 0; i < 4; ++i) {
		std::cout << comp_number[i];
	}
	std::cout << std::endl;*/
}
void BullsandCows::check(int number) {
	if (number < 1000 || number >= 10000) {
		throw std::logic_error ("Ошибка ввода: число не принадлежит правильному диапазону!"); 
	}
}
void BullsandCows::convert_number_to_mass(int number, int* mass) {
	for (int i = 0; i < 4; i++) {
		mass[i] = -1;
	}
	for (int i = 3; i >= 0; i--) {
		int digit = number % 10;

		//проверка на дубликаты
		for (int j = 0; j < 4; j++) {
			if (mass[j] == digit) {
				throw std::invalid_argument("Ошибка ввода: дубликат цифры!");
			}
		}
		mass[i] = digit; 
		number /= 10; 
	}
}
bool BullsandCows::input_user_number(int* user_number) {
	int number;
	std::cout << "Введи число: ";
	std::cin >> number;

	try {
		check(number);
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
		std::cout << " Попробуйте снова." << std::endl;
		return false;
	}

	try {
		convert_number_to_mass(number, user_number);
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
		std::cout << " Попробуйте снова." << std::endl;
		return false;
	}
	return true;
}
int BullsandCows::calculate_bulls(int* comp_number, int* user_number) {
	int bulls = 0;
	for (int i = 0; i < 4; i++) {
		if (comp_number[i] == user_number[i]) {
			bulls++;
		}
	}
	return bulls;
}
int BullsandCows::calculate_cows(int* comp_number, int* user_number) {
	int cows = 0;
	bool user_used[4] = { false };

	for (int i = 0; i < 4; i++) {
		if (comp_number[i] == user_number[i]) {
			user_used[i] = true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (user_used[i] == false) {
			for (int j = 0; j < 4; j++) {
				if (user_number[i] == comp_number[j]) {
					cows++;
				}
			}
		}	
	}
	return cows;
}
bool BullsandCows::check_win(int bulls) {
	return bulls == 4; 
}
void BullsandCows::print_win_message() {
	std::cout << "Вы верно угадали число! Поздравляю! ";
}
