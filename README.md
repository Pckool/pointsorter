# Point Sorter Project
### By Philippe Clesca

## DESCRIPTION
	With my approach to this project, I wanted to learn how use pointers, how to effectivey use malloc, and how to dynamically allocate space for unkowns.

## HOW IT WORKS
	1. Check if the arg is valid (is not null, there is only one arg, etc.)
	2. If the arg is valid, it gets passed to the `stringParser` function, which is used to find the preform operations on the found strings.
	3. `stringParser` goes to `findWords`, a function that accepts a string and a starting index. It starts at theindex given and keeps ince=rementing through the given string untill It finds: 
		a) The index of the fisrt alphabetic character
		b) The index of the first non-alphabetic character after the n amount of alphabetic characters
	it then returns both in an array.
	4. The `stringParser` function now takes that, extracts the characters within the defined indexes, and forms a string from the chars (its essentially a substring), then sends that to `sortWords`
	5a. `sortWords` takes an array (either empty or populated) and the substring mentioned in step 4 and DYNAMICALLY adds the substring to that array (no wasted space). 	
	5b. `sortWords` then sorts the array using qsort (which analyses the characters of the string and determines which string is "less" or "more" using the strcmp operation.) It then returns the sorted array.
	6. Repeat steps 3-5 until we are done with the string
	7. Print out the sorted array BACKWARDS.
 
---
## OTHER NOTES
	- I begain by using a linked list for storing and sorting and recognized why you were leaning against it in class. It's not that it is hard, it is just more complecated and it added more functions and mallocs then I believe was needed for the project.
