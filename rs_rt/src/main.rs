use clap::Parser;
use rt_rs::{aa_seq, non_aa_seq};

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
   /// Name of the person to greet
   #[arg(short, long)]
   file: String,

   /// Number of times to greet
   #[arg()]
   a: Option<bool>,
}


fn main() {
    let len = std::env::args().len();
    let args = Args::parse();
    if len != 2 && len != 3
	{
		println!("Usage ./RTv1 map");
		println!("OR");
		println!("Usage ./RTv1 map -a");
	}
	else
	{
		match args.a {
				Some(aliasing) => {
					if aliasing {
						aa_seq(&args.file);
					} else {
						non_aa_seq(&args.file);
					}
				},
				None => non_aa_seq(&args.file)
		}
	}
}
