"""Train using explicitly selected local weights and a dataset configuration."""
import argparse
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--weights", type=Path, required=True)
    parser.add_argument("--data", type=Path, required=True)
    parser.add_argument("--epochs", type=int, default=500)
    parser.add_argument("--output", type=Path, default=ROOT / "outputs/training")
    args = parser.parse_args()
    if args.epochs < 1:
        parser.error("--epochs must be positive")
    for path in (args.weights, args.data):
        if not path.is_file():
            parser.error(f"Required file does not exist: {path}")
    from ultralytics import YOLO
    model = YOLO(str(args.weights))
    model.train(data=str(args.data.resolve()), epochs=args.epochs,
                project=str(args.output.resolve()))


if __name__ == "__main__":
    main()
