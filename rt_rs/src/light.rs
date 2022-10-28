use libc::c_int;

use crate::world::cnt_space;


pub fn check_light(str: &Vec<&str>, i: &mut usize, chk: &mut c_int)
{
	let mut t= cnt_space(str[*i], i, chk, 2);

	if t != 1 {
		eprintln!("Light Error in name");
  }
	else
	{
		let s: Vec<&str> = str[*i - 1].split(' ').collect();
		t = s[1].parse::<i32>().unwrap();
	}
	let mut lines = 1;
	while lines < t.try_into().unwrap() && str.get(*i + lines).unwrap().chars().nth(0).unwrap().is_numeric() {
		lines += 1;
  }
	if lines != t.try_into().unwrap() {
		*chk = 0;
  }
	lines = 0;
	while lines < t.try_into().unwrap()
	{
		if cnt_space(str[*i], i, chk, 2) != 1 {
			eprintln!("Light Error in coordinates");
    }
		lines += 1;
	}
}