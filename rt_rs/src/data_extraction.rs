use crate::object::ObjectItem;

pub fn get_reflect_refract(line: &str, obj: &mut ObjectItem) {
  let props: Vec<&str> = line.split(' ').collect();
	obj.reflect = props.first().unwrap().parse::<f32>().unwrap() / 100.;
	obj.refract = props.get(1).unwrap().parse::<i32>().unwrap();
}

pub fn get_obj_options(line: &str, obj: &mut ObjectItem) {
  let props: Vec<&str> = line.split(' ').collect();
	// if (ft_atoi(s[0]))
	// 	obj.c = ft_rand(obj.c);
	obj.pattern = props.get(1).unwrap().parse::<i32>().unwrap();
	obj.filter = props.get(2).unwrap().parse::<i32>().unwrap();
}

pub fn get_rad_h(line: &str, obj: &mut ObjectItem) {
  if line.contains(' ') {
    let props: Vec<&str> = line.split(' ').collect();
    obj.rad = props.first().unwrap().parse::<f32>().unwrap();
    obj.h = props.get(1).unwrap().parse::<f32>().unwrap();
  } else {
    obj.rad = line.parse::<f32>().unwrap();
  }
}