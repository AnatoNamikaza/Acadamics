bool finishCourses(int numCourses, vector<vector<int>> req) {
	vector<int> read_course;

	int i, j, total_course, rept = 0;

	for (i = 0; read_course.size() <= numCourses && i < req.size(); i++)
	{
		for (j = 0; j < read_course.size(); j++) {
			if (read_course[j] == req[i][0]) {
				goto L1;
			}
		}
		read_course.push_back(req[i][0]);
	L1:
		continue;
	}

	for (i = 0; read_course.size() <= numCourses && i < req.size(); i++)
	{
		for (j = 0; j < read_course.size(); j++) {
			if (read_course[j] == req[i][1]) {
				rept++;
				goto L2;
			}
		}
		read_course.push_back(req[i][1]);
	L2:
		continue;
	}

	total_course = read_course.size();

	for (i = 0; i <= rept; i++)
	{
		if (total_course + i == numCourses)
			return true;
	}


	return false;
}