#include <stdio.h>

int demander_nombre(void);
int isLeapYear(int y);
int DaysForMonth(int year, int month);

int demander_nombre(void) {
	int a;
 
	do {
	printf("Enter an integer representing the number of days passed since Epoch.\n");
	scanf("%d", &a);
	
	} while (a < 1);
 
	return a;
}

int isLeapYear(int y) {
	if ((y % 400) == 0) {
		return 1;
	} else if ((y % 100) == 0) {
		return 0;
	} else if ((y % 4) == 0) {
		return 1;
	} else {
		return 0;
	}
}

int DaysForMonth(int year, int month) {
	switch(month) {
		case 1: return 31;
		break;
		case 2: if (isLeapYear(year)) {
			return 29;
		} else {
			return 28;
		}
		break;
		case 3: return 31;
		break;
		case 4: return 30;
		break;
		case 5: return 31;
		break;
		case 6: return 30;
		break;
		case 7: return 31;
		break;
		case 8: return 31;
		break;
		case 9: return 30;
		break;
		case 10: return 31;
		break;
		case 11: return 30;
		break;
		case 12: return 31;
		break;
		default: 
		return 0;
		break;
	}
	
}

int main(void) {
	int days = demander_nombre();       /* 31 décembre 2008, normalement lu depuis la puce */
    int year = 1980;  /* 1980, l'epoch pour Microsoft */
    int month = 1;

    while (days > 365) {
        if (isLeapYear(year)) { /* 2008 est une année bissextile */
            if (days >= 366) {
                days -= 366;
                year += 1;
            }
        }
        else {
			
            days -= 365;
            year += 1;
        }
    }
    
    while (days > 30) {
        
          days = days - DaysForMonth(year, month);
          month += 1;
        
    }
    
    printf("%d / %d / %d", days, month, year);
    return 0;
}
