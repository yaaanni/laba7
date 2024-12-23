#include "utils.h"
#include <limits>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

typedef unsigned long long ull;
typedef long long ll;

std::string add_in_base(const std::string& num1, const std::string& num2, short base) {
    std::string result;
    int carry = 0;
    int maxLength = std::max(num1.size(), num2.size());
    for (int i = 0; i < maxLength || carry; i++) {
        int digit1 = (i < num1.size()) ? base_symbols.find(num1[num1.size() - 1 - i]) : 0;
        int digit2 = (i < num2.size()) ? base_symbols.find(num2[num2.size() - 1 - i]) : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / base; 
         
        result += base_symbols[sum % base];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtract_in_base(const std::string& num1, const std::string& num2, short base, ll number1, ll number2) {
    if (number2 > number1) {
        return "-" + subtract_in_base(num2, num1,base,number2,number1);
    }
    std::string result;
    int difference;
    int borrow = 0;
    int maxLength = std::max(num1.size(), num2.size());
    for (int i = 0; i < maxLength; i++) {
        int digit1 = (i < num1.size()) ? base_symbols.find(num1[num1.size() - 1 - i]) : 0;
        int digit2 = (i < num2.size()) ? base_symbols.find(num2[num2.size() - 1 - i]) : 0;
        digit1 -= borrow;
        if (digit1 < digit2) {
            digit1 += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        difference = digit1 - digit2;
        result += base_symbols[difference];
    }
    while (result.size() > 1 && result.back() == base_symbols[0]) {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void Task::task1() {
    std::cout << "Введите число в двоичном представлении в формате (знаковый бит + ноль + само число): \n";
    std::string number;

    while (true) {
        std::getline(std::cin, number);
        bool valid = true;

        if ((number.length() < 3) || (number[1] != '0')) {
            std::cout << "Следуйте вводимому формату. Введите число заново: \n";
            valid = false;
        }
        
        if (number.find_first_not_of("01") != std::string::npos) {
            std::cout << "Можно вводить только 0 или 1, введите число заново: \n";
            valid = false;
        }

        if (valid) {
            break;
        }
    }

    if (number[0] == '0') {
        std::cout << "Введенное положительное число в прямом коде: \n" << number;
    } else {
        std::string newString = number.substr(1);
        for (char &c : newString) {
            c^=1;
        }
        newString = "1"+newString;
        std::cout << "Введенное отрицательное число в обратном коде: \n" << newString;
    }
}

void Task::task2() {
    {
    std::string digit_str1;
    std::string digit_str2;
    std::cout << "Введи число 1: ";
    std::cin >> digit_str1;
    std::cout << "Введи число 2: ";
    std::cin >> digit_str2;
    if (digit_str1 == "-0") {
        digit_str1 = "0";
    }
    if (digit_str2 == "-0") {
        digit_str2 = "0";
    }
    if (digit_str1 == "0" && digit_str2 == "0") {
        std::cout << "Сумма двух нулей в прямом коде - " << "00";
    }
    else {
        std::string binary1 = binary_converting(digit_str1);
        std::string binary2 = binary_converting(digit_str2);
        auto [binary1_1, binary2_2] = equalize_lengths(binary1, binary2);//сразу с двумя переменными рабоатаем
        std::cout << "Число " << digit_str1 << " в прямом коде : " << binary1_1 << std::endl;
        std::cout << "Число " << digit_str2 << " в прямом коде : " << binary2_2 << std::endl;
        binary1_1 = convert_to_complement(convert_to_reverse(binary1_1));
        binary2_2 = convert_to_complement(convert_to_reverse(binary2_2));
        std::cout << "Число " << digit_str1 << " в дополнительном коде : " << binary1_1 << std::endl;
        std::cout << "Число " << digit_str2 << " в дополнительном коде : " << binary2_2 << std::endl;
        std::string sum = add(binary1_1,binary2_2);
        std::cout << "Сумма чисел " << digit_str1 << " и " << digit_str2 << " в дополнительном коде - " << sum << std::endl;
        std::cout << "Сумма чисел " << digit_str1 << " и " << digit_str2 << ", переведенная из доп. кода в прямой - " << back_convert(compelement_to_reverse(sum));
    }
}
}

void Task::task3() {
    std::string final;
    ll number1, number2;
    char sign;
    short base;

    std::cout << "Введите систему исчисления: ";
    std::cin >> base;

    // Проверка диапазона системы счисления
    if (base < 2 || base > 62) {
        std::cout << "Система исчисления должна быть в диапазоне от 2 до 62.\n";
        return;
    } else {
        std::cout << "В выбранной системе исчисления присутствуют следующие символы: " << base_symbols.substr(0, base);
        std::cout << "\n\nВведите первое число в десятичной форме: ";
        std::cin >> number1;
        std::cout << "Введите второе число в десятичной форме: ";
        std::cin >> number2;
        std::cout << "Хотите сложить (напишите +), вычесть (любой другой символ (-)): ";
        std::cin >> sign;

        std::cout << "\nПервое число в данной системе исчисления - " << convert_to_any_base(number1, base);
        std::cout << "\nВторое число в данной системе исчисления - " << convert_to_any_base(number2, base);

/*
            СЛОЖЕНИЕ:
+ +  ==== обычное сложение
+ -   ==== вычитание
- +  ==== вычитание в обратном порядке
- - ==== сложить положительные и - в начале
            ВЫЧИТАНИЕ:
+ + === обычное вычитание
+ - ==== сложение положительных
- + ==== сложить положительные и - в начале
- - ===== вычитание в обратном порядке
*/

// Сложение
        if (sign == '+') {
            if (number1 >= 0 && number2 >= 0) {
                final = add_in_base(convert_to_any_base(number1,base),convert_to_any_base(number2,base),base);
            } else if (number1 >= 0 && number2 <0) {
                final = subtract_in_base(convert_to_any_base(number1,base),convert_to_any_base(number2*-1,base),base,number1,number2*-1);
            } else if (number1 < 0 && number2 >= 0) {
                final = subtract_in_base(convert_to_any_base(number2,base),convert_to_any_base(number1*-1,base),base,number2,number1*-1);
            } else if (number1 < 0 && number2 < 0) {
                final = "-" + add_in_base(convert_to_any_base(number1*-1,base),convert_to_any_base(number2*-1,base),base);
            }
        std::cout << "\nСумма ваших чисел в данной системе исчисления - " << final;
        } else {
            if (number1 >= 0 && number2 >= 0) {
                final = subtract_in_base(convert_to_any_base(number1,base),convert_to_any_base(number2,base),base,number1,number2);
            } else if (number1 >= 0 && number2 <0) {
                final = add_in_base(convert_to_any_base(number1,base),convert_to_any_base(number2*-1,base),base);
            } else if (number1 < 0 && number2 >= 0) {
                final = "-" + add_in_base(convert_to_any_base(number1*-1,base),convert_to_any_base(number2,base),base);
            } else if (number1 < 0 && number2 < 0) {
                final = subtract_in_base(convert_to_any_base(number2*-1,base),convert_to_any_base(number1*-1,base),base,number2*-1,number1*-1);
            }
        std::cout << "\nРазность ваших чисел в данной системе исчисления - " << final;
        }
    }
}

bool isItNumber(char c) {
    return (c >= '0' && c <= '9');
}

long long validateInputt() {
    std::string stroka;
    while (true) {
        std::cin >> stroka;
        bool isNumber = true;

        for (size_t i = 0; i < stroka.length(); ++i) {
            if (i == 0 && stroka[i] == '-') {
                continue;
            }
            if (!isdigit(stroka[i])) {
                isNumber = false;
                break;
            }
        }

        if (isNumber) { // преобразовываем строку в лонг лонг
            try {
                return std::stoll(stroka);
            } catch (const std::out_of_range&) {
                std::cerr << "Число вне допустимого диапазона\n";
            } catch (const std::invalid_argument&) {
                std::cerr << "Некорректный ввод\n";
            }
        } else {
            std::cerr << "Ошибка ввода\n";
        }
    }
}

bool isDivisible(long long a, long long k) {
    long long plus = (k + 1) >> 1;//учитываем четные и нечетные числа, чтобы не терять остаток
    while (a > k) {
        a = (a >> 1) + ((a & 1) ? plus : 0);//проверка на нечетность, в случае нечетности добавляется значение plus
    }
    return (a == k || a == 0);//тру если число нацело делиться
}

void Task::task4() {
    long long a;

    std::cout << "Введите число: \n";
    a = validateInputt();
    if (a < 0) a = ~a + 1;// преобразование отрицательного числа(доп код) в его положительную форму в доп коде 
    std::cout 
    << a << " делится на 7  \t- " << (isDivisible(a, 7) ? "True" : "False") << "\n"
    << a << " делится на 23 \t- " << (isDivisible(a, 23) ? "True" : "False") << "\n"
    << a << " делится на 197\t- " << (isDivisible(a, 197) ? "True" : "False") << "\n";
}

void Task::task5() {
    bool slaves[COUNT_SLAVES] = {true, true, true, true, true};//массив пока что живых рабов
    bool barrels[COUNT_BARRELS];//массив из бочек
    for(int i = 0; i < COUNT_BARRELS; ++i) {
        barrels[i] = true;// все бочки безопасны
    }
    std::cout << "\nВведи номер отравленной бочки: ";
    short index_poison;
    std::cin >> index_poison;
    bool flag = false;
    while(!flag){
        if(std::cin.fail() || index_poison <= 0 || index_poison > 240) {
            std::cin.clear(); // Сброс состояния ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
            std::cout << "Неправильно ввели номер отравленной бочки! Попробуйте снова: ";
            std::cin >> index_poison;
        } else {
            flag = true;
        }
    }

    barrels[index_poison-1] = false;//пометили отравленную бочку
    short count_survived = 0; //для отслеживания выживших после первого дня
    DAY1(slaves, barrels, count_survived);
    int num_possible_options = pow(2, count_survived);// количество возможных вариантов: раб может иметь два варианта: выжил или мертв, возводим в степень выживших рабов после первого дня 
    DAY2(num_possible_options,slaves,barrels);
}

std::string back_convert(const std::string& bin_str) {
    if (bin_str[0] == '0') { return bin_str; }
    std::string number = bin_str.substr(1);  
    for (char &bit : number)
        bit^=1;
    return "1"+number;
}

std::string compelement_to_reverse(const std::string& bin_str) {
    if (bin_str[0] == '0') { return bin_str; } 
    std::string invertedCode = bin_str;
    for (int i = bin_str.length() - 1; i >= 0; --i) {
        if (bin_str[i] == '1') {
            invertedCode[i] = '0';
            break;
        } else {
            invertedCode[i] = '1';
        }
    }
    return invertedCode;
}

std::string add(const std::string& num1, const std::string& num2) {
    std::string result(num1.length(), '0');
    bool carry = false;//для переноса
    for (int i = num1.length() - 1; i >= 0; --i) {
        bool bit1 = num1[i] == '1';
        bool bit2 = num2[i] == '1';
        bool sum = bit1 ^ bit2 ^ carry;//тру если тру нечетное колво
        carry = (bit1 && bit2) || (carry && (bit1 || bit2));
        result[i] = sum ? '1' : '0';
    }
    return result; 
}

std::string pad_with_zeros(const std::string& bin_str, size_t target_length) {
    if (bin_str.length() >= target_length) {
        return bin_str; 
    }
    size_t zeros_to_add = target_length - bin_str.length();//вычисляем количество нулей,которое нужно добавить
    std::string padded_str = bin_str;
    std::string number_part = padded_str.substr(1);
    padded_str = padded_str[0] + std::string(zeros_to_add, '0') + number_part; 
    return padded_str;
}

std::pair<std::string, std::string> equalize_lengths(const std::string& num1, const std::string& num2) { //работаю с парой строк
    size_t max_length = std::max(num1.length(), num2.length());
    std::string padded_num1 = pad_with_zeros(num1, max_length);
    std::string padded_num2 = pad_with_zeros(num2, max_length);
    return {padded_num1, padded_num2}; 
}

std::string convert_to_reverse(const std::string& bin_str) {
    if (bin_str.length() < 3 || (bin_str[0] != '0' && bin_str[0] != '1') || (bin_str.find_first_not_of("01") != std::string::npos)) {
        return "Число в прямом коде введено неверным образом";}
    if (bin_str[0] == '0') { return bin_str; }
    std::string number = bin_str.substr(1);  
    for (char &bit : number)
        bit^=1;
    return "1"+number;
}

std::string convert_to_complement(const std::string& bin_str) {
    if (bin_str[0] == '0') { return bin_str; }
    std::string complement = bin_str.substr(1);  
    bool carry = true; //для добавления единицы если 1+1 то 0 но carry тру что предоставляет перенос единицы
    for (int i = complement.length() - 1; i >= 0; --i) {
        if (carry) {
            if (complement[i] == '0') {
                complement[i] = '1'; 
                carry = false; 
            } else {
                complement[i] = '0'; 
            }
        }
    }
    if (carry) {
        complement = '1' + complement;
    }
    return "1" + complement;
}

std::string binary_converting(const std::string digit_str) {
    std::string binary = "";
    bool negative_sign = false;
    ull remainder_of_2 = 0;
    std::string number_no_sign = digit_str;//для копии строки без знака если число отриц
    if (digit_str[0] == '-') {
        negative_sign = true;
        number_no_sign = digit_str.substr(1); 
    }
    std::string temp = number_no_sign;
    while (temp != "0") {
        remainder_of_2 = 0;
        std::string newTemp = "";
        for (auto digit : temp) {
            ll current = remainder_of_2 * 10 + (digit - '0');
            newTemp += (current / 2) + '0';
            remainder_of_2 = current % 2;
        }
        while (newTemp.length() > 1 && newTemp[0] == '0') {
            newTemp.erase(0, 1);//удаляем ненужные нули спереди
        }
        binary.push_back(remainder_of_2 + '0');// остаток преобразуем в символ и закидываеме в конец
        temp = newTemp;//актуальное значение строки для след цикла
    }
    std::reverse(binary.begin(), binary.end());
    if (negative_sign) { binary = "10" + binary; } 
    else { binary = "00" + binary;}
    return binary;
}

std::string convert_to_any_base(ll number_in_10, short base) {
    if (number_in_10 == 0) { return "0";}
    int remainder;
    std::string result = "";
    ll number_in_10_abs = std::abs(number_in_10);//для обработки отрицательных чисел 
    while (number_in_10_abs > 0) {
        remainder = number_in_10_abs % base;
        result = base_symbols[remainder] + result;
        number_in_10_abs /= base;
    }
    if (number_in_10 < 0) {
        result = "-" + result;
    }
    return result;
}

void DAY1(bool slaves[COUNT_SLAVES], const bool barrels[COUNT_BARRELS], short &count_survived) {
    std::string barrels_3 = "10000";//для каждой бочки обновляем значение
    /*
    0 - раб пьет в первый день
    1 - во второй день
    2 - вообще не пьет
    */ 
    for(int k = 0; k < COUNT_BARRELS; ++k) {
        for(int i = 0; i < COUNT_SLAVES; ++i) {
            if(barrels_3[i] == '0') {
                slaves[i] *= barrels[k];
            }
        }
        for(int i = 0; i < COUNT_SLAVES; ++i) {
            if(barrels_3[i] == '2') {
                barrels_3[i] = '0';
            } else {
                barrels_3[i]++;
                break;
            }
        }

    }
    std::cout << "\n\nПрошел 1-ый день...\n\n";
    for(int i = 0; i < COUNT_SLAVES; ++i) {
        if(slaves[i]) {
            count_survived++; //если раб жив, то увеличиваем счетчик выживших
            std::cout << "Раб " << '<' << i+1 << '>' << " выжил\n";
        } else {
            std::cout << "Раб " << '<' << i+1 << '>' << " погиб\n";
        }
    }
}

void GET_LAST_SURVIVED(bool slaves[COUNT_SLAVES], bool last_survived[COUNT_SLAVES]) {
    for(int i = 0; i < COUNT_SLAVES; ++i) {
        if(slaves[i]) {
            last_survived[i] = true;
        } else {
            last_survived[i] = false;  
        }
    }
}

void GET_RESULT(const bool slaves[COUNT_SLAVES], bool last_survived[COUNT_SLAVES]) {
    std::string result_str;
    for(int i = 0; i < COUNT_SLAVES; ++i) {
        if(slaves[i] && last_survived[i]) {
            result_str.push_back('2');
        } else if(slaves[i] && !last_survived[i]) {
            result_str.push_back('1');
        } else {
            result_str.push_back('0');
        }
    }
    short result = 0;
    for(int k = 0; k < COUNT_SLAVES; ++k) {
        result += pow(3, k) * (result_str[k] - '0');
    }
    std::cout << "\n\nПрошел 2-ой день...\n\n";
    for(int i = 0; i < COUNT_SLAVES; ++i) {
        if(last_survived[i]) {
            std::cout << "Раб " << '<' << i+1 << '>' << " выжил\n";
        } else {
            std::cout << "Раб " << '<' << i+1 << '>' << " погиб\n";
        }
        
    }
    std::cout << "\n\nЯд находится в бочке под номером " << '[' << result << ']' << '\n';
}
void DAY2(const int num_possible_options, bool slaves[COUNT_SLAVES], const bool barrels[COUNT_BARRELS]) {
    char maybe_index_poison_3[num_possible_options][COUNT_SLAVES];//массив для возможных комбинаций для отравленных бочек 
    bool last_survived[COUNT_SLAVES];//выжившие
    std::vector<short> maybe_index_poison;//возможные номера отравленных бочек
    std::string str_possible_options = "11111111111111111111111111111111";//строка для генерации возможных комбинаций
    for(int k = 0; k < num_possible_options; ++k) {
        for(int i = 0; i < 32; ++i) {
            if(str_possible_options[i] == '2') {
                str_possible_options[i] = '1';
            } else {
                str_possible_options[i]++;
                break;
            }
        }
        for(int j = 0, s = 0; j < COUNT_SLAVES; ++j) {
            if(!slaves[j]) {
                maybe_index_poison_3[k][j] = '0';
            } else {
                maybe_index_poison_3[k][j] = str_possible_options[s++];
            }
        }
        
    }
    short sum = 0;
    for(int i = 0; i < num_possible_options; ++i) {
        for(int k = 0; k < COUNT_SLAVES; ++k) {
            sum += pow(3, k) * (maybe_index_poison_3[i][k] - '0');
        }
        maybe_index_poison.push_back(sum);
        sum = 0;
    }
    std::cout << "\n\nВозможно отравлены следующие бочки: ";//после пересмотра возможных комбинаций получили бочки которые могут быть отравлены
    for(auto i : maybe_index_poison) {
        std::cout << '[' << i << ']' << ',' << ' ';
    }

    GET_LAST_SURVIVED(slaves, last_survived);  //вызываем данную функцию для получения массива состояния выживших рабов
    for(int j = 0; j < num_possible_options; ++j) {
        for(int i = 0; i < COUNT_SLAVES; ++i) {
            if(maybe_index_poison_3[j][i] == '1') {
                last_survived[i] *= barrels[maybe_index_poison[j] - 1];
            }
        }
    }

    GET_RESULT(slaves, last_survived);
}
