int minParenToAdd(string s) {

	int count1 = 0, count2 = 0, i = 0;
	for (; i < s.length(); i++)
	{
		if (s[i] == '(') {
			count1++;
		}
		else if (s[i] == ')' && count1 > 0) {
			count1--;
		}
		else if (s[i] == ')' && count1 == 0) {
			count2++;
		}
	}

	return count1 + count2;
}
