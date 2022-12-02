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
    let args = Args::parse();
		if args.aa {
			aa_seq(&args.file);
		} else {
			non_aa_seq(&args.file);
		}
}
