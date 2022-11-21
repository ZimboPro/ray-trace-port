use libc::{c_int, c_float};

fn noise2(x: c_float, y: c_float, seed: c_float) -> c_float
{
	let hash: Vec<usize> = vec![208, 34, 231, 213, 32, 248, 233, 56, 161, 78, 24, 140,
					71, 48, 140, 254, 245, 255, 247, 247, 40, 185, 248, 251,
					245, 28, 124, 204, 204, 76, 36, 1, 107, 28, 234, 163, 202,
					224, 245, 128, 167, 204, 9, 92, 217, 54, 239, 174, 173, 10,
					193, 189, 190, 121, 100, 108, 167, 44, 43, 77, 180, 204, 8,
					81, 70, 223, 11, 38, 24, 254, 210, 210, 177, 32, 81, 195,
					243, 125, 8, 169, 112, 32, 97, 53, 195, 13,
					203, 9, 47, 104, 125, 117, 114, 124, 165, 203, 181, 235,
					193, 206, 70, 180, 174, 0, 167, 181, 41,
					164, 30, 116, 127, 198, 245, 146, 87, 224, 149, 206, 57,
					4, 192, 210, 65, 210, 129, 240, 178, 105,
					228, 108, 245, 148, 140, 40, 35, 195, 38, 58, 65, 207,
					215, 253, 65, 85, 208, 76, 62, 3, 237, 55, 89,
					232, 50, 217, 64, 244, 157, 199, 121, 252, 90, 17,
					212, 203, 149, 152, 140, 187, 234, 177, 73, 174,
					193, 100, 192, 143, 97, 53, 145, 135, 19, 103, 13, 90,
					135, 151, 199, 91, 239, 247, 33, 39, 145,
					101, 120, 99, 3, 186, 86, 99, 41, 237, 203, 111, 79,
					220, 135, 158, 42, 30, 154, 120, 67, 87, 167,
					135, 176, 183, 191, 253, 115, 184, 21, 233, 58, 129,
					233, 142, 39, 128, 211, 118, 137, 139, 255,
					114, 20, 218, 113, 154, 27, 127, 246, 250, 1, 8, 198,
					250, 209, 92, 222, 173, 21, 88, 102, 219];
  let t: usize = (y as usize + seed as usize) % 256;
  let t2: usize = (hash[t] + x as usize) % 256;

	return (hash[((hash[t]) + x as usize) % 256]) as c_float;
}

fn lin_inter(x: c_float, y: c_float, s: c_float) -> c_float
{
	return x + s * (y - x);
}

fn smooth_inter(x: c_float, y: c_float, s: c_float) -> c_float
{
	return lin_inter(x, y, s * s * (3. - 2. * s));
}

fn	noise2d(x: c_float, y: c_float) -> c_float
{
	let seed = 179.;

	let x_int = x;
	let y_int = y;
	let x_frac = x - x_int;
	let y_frac = y - y_int;
	let s = noise2(x_int, y_int, seed);
	let t = noise2(x_int + 1., y_int, seed);
	let u = noise2(x_int, y_int + 1., seed);
	let v = noise2(x_int + 1., y_int + 1., seed);
	let low = smooth_inter(s, t, x_frac);
	let high = smooth_inter(u, v, x_frac);
	return (smooth_inter(low, high, y_frac));
}

#[no_mangle]
pub unsafe extern "C" fn perlin2d( x: c_float,  y: c_float,  freq: c_float, depth: c_int) -> c_float
{

	let mut xa = x * freq;
	let mut ya = y * freq;
	let mut amp = 1.0;
	let mut fin = 0.;
	let mut div = 0.0;
	let mut i = 0;
	while i < depth
	{
		div += 256. * amp;
		fin += noise2d(xa, ya) * amp;
		amp /= 2.;
		xa *= 2.;
		ya *= 2.;
		i += 1;
	}
	return (fin / div);
}