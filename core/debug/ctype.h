/*
 * MIT License
 *
 * Copyright (c) 2020 Tiago Vasconcelos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @brief - C Standard Library that declares several functions that are useful for testing and mapping characters.
 * @date  - 11-07-2017
 *
 */

#ifndef __CTYPE_H__
#define __CTYPE_H__

#include "types.h"


/**
 * @brief check if given char is a digit
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole digits { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
 *
 */
T_BOOL isdigit(T_CHAR c);

/**
 * @brief check if given char is a hexadecimal digit
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole hexa digits { 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f }.
 *
 */
T_BOOL isxdigit(T_CHAR c);

/**
 * @brief check if given char is a octal digit
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole octal digits { 0, 1, 2, 3, 4, 5, 6, 7 }.
 *
 */
T_BOOL iscdigit(T_CHAR c);

/**
 * @brief check if given char is a binary digit
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole binary digits { 0, 1 }.
 *
 */
T_BOOL isbdigit(T_CHAR c);

/**
 * @brief check if given char is alphabetic
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of alphabetic chars { lowercase letters and uppercase letters. }.
 *
 */
T_BOOL isalpha(T_CHAR c);

/**
 * @brief check if given char is alphanumeric
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of alphanumeric chars { digits, lowercase letters and uppercase letters. }.
 *
 */
T_BOOL isalnum(T_CHAR c);

/**
 * @brief check if given char is a uppercase letter
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole upper case letters {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }.
 *
 */
T_BOOL isupper(T_CHAR c);

/**
 * @brief check if given char is a lowercase letter
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole lower case letters { a b c d e f g h i j k l m n o p q r s t u v w x y z }.
 *
 */
T_BOOL islower(T_CHAR c);

/**
 * @brief check if given char is a space char
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole space chars { tab(\t), space( ), newline(\n), carriage return(\r) }.
 *
 */
T_BOOL isspace(T_CHAR c);

/**
 * @brief check if given char is a ponctuation char
 * @param[in] c - Char to test.
 * @return TRUE if the char belongs to the set, FALSE otherwise
 *
 * Set of whole ponctuation chars { ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~ }.
 *
 */
T_BOOL ispunct(T_CHAR c);

/**
 * @brief convert upper case letter to lowercase, all other chars remain the same.
 * @param[in] c - Char to convert.
 * @return Converted char.
 *
 */
T_CHAR tolower(T_CHAR c);

/**
 * @brief convert lower case letter to upper case, all other chars remain the same.
 * @param[in] c - Char to convert.
 * @return Converted char.
 *
 */
T_CHAR toupper(T_CHAR c);

/**
 * @brief convert all chars in string to lower case.
 * @param[in] c - String to convert.
 * @return Converted char.
 *
 */
T_VOID strtolower(T_STRING str);

/**
 * @brief convert all chars in string to upper case.
 * @param[in] c - String to convert.
 * @return Converted char.
 *
 */
T_VOID strtoupper(T_STRING str);


#endif /* __CTYPE_H__ */
