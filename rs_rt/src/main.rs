use clap::Parser;
use rt_rs::{aa_seq, non_aa_seq};

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
   /// File name of the world
   #[arg(short, long, )]
   file: String,

   /// Enable antialiasing
   #[arg(short, long)]
   aa: bool,
}


fn main() {
    let len = std::env::args().len();
    let args = Args::parse();
		// println!(le)
  //   if len != 2 && len != 3
	// {
	// 	println!("Usage ./RTv1 map");
	// 	println!("OR");
	// 	println!("Usage ./RTv1 map -a");
	// }
	// else
	// {
		if args.aa {
			aa_seq(&args.file);
		} else {
			non_aa_seq(&args.file);
		}
		// match args.aa {
		// 		Some(aliasing) => {
		// 			if aliasing {
		// 			} else {
		// 			}
		// 		},
		// 		None => non_aa_seq(&args.file)
		// }
	// }
}
