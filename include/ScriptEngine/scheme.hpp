    internal enum CellType
    {
        Atom, // 原子为标识符形式的符号或数字的字面值   如果是原子，或者空表 返回t ，否则就返回 f
        Quote, // 引用，用来表示数据 ，避免被求值
        Operater, // 算术操作符
        FucntionCall, // 函数调用
        Lambda, // 匿名函数
        Integer, // 整数
        Syntax, // 语法关键词
        Nil, // 空序对
        Pair, // 序对
        Symbol, // 符号
        Closure, // 闭包
        SpecialSymbol, // 特殊符号

    }
	
	  internal class Pair
    {
        private static List<string> Syntaxs = new List<string>()
        {
            "car", "cdr", "cons", "atom", "quote", "cond", "let", "lambda", "'", "if"
        };

        private static List<string> Operates = new List<string>()
        {
            "+", "-", "*", "/", "%", "="
        };

        private static List<string> SpecialSymbol = new List<string>()
        {
            "#f", "#t"
        };

        public CellType Type = CellType.Pair;

        private int intData = 0;
        private string stringData = "";

        public Pair()
        {
            Type = CellType.Nil;
        }

        public Pair(Pair _car, Pair _cdr)
        {
            if (Operates.Contains(_car))
            {
                stringData = _car;
                cdr = _cdr;
                Type = CellType.Operater;
            }
            else if (Syntaxs.Contains(_car))
            {
                if (_car == "lambda")
                {
                    _car.Type = CellType.Lambda;
                    car = _car;
                    cdr = _cdr;
                }
            }
            else
            {
                car = _car;
                cdr = _cdr;
            }

            if (_car.Type == CellType.Closure)
            {
                Type = CellType.FucntionCall;
            }
        }

        public Pair car { get; set; }

        public Pair cdr { get; set; }



        //需要显示转换的用这个  explicit
        public static implicit operator int(Pair x)
        {
            return (int) x.intData;
        }

        public static implicit operator Pair(int x)
        {
            Pair a = new Pair();
            a.intData = x;
            a.Type = CellType.Integer;
            a.car = a;
            return a;
        }

        //需要显示转换的用这个  explicit
        public static implicit operator bool(Pair x)
        {
            return x.stringData == "#t";
        }

        public static implicit operator Pair(bool x)
        {
            Pair a = new Pair();
            a.stringData = x ? "#t" : "#f";
            a.Type = CellType.SpecialSymbol;
            a.car = a;
            return a;
        }

        //需要显示转换的用这个  explicit
        public static implicit operator string(Pair x)
        {
            return (string) x.stringData;
        }

        public static implicit operator Pair(string x)
        {
            Pair a = new Pair();
            a.stringData = x;
            int intV = 0;
            if (Syntaxs.Contains(x))
            {
                if (x == "lambda")
                {
                    a.Type = CellType.Lambda;
                }
                else if (x == "quote" || x == "'")
                {
                    a.Type = CellType.Quote;
                }
                else
                {
                    a.Type = CellType.Syntax;
                }
            }
            else if (Operates.Contains(x))
            {
                a.Type = CellType.Operater;
                a.cdr = new Pair();
            }
            else if (int.TryParse(x, out intV))
            {
                a.intData = intV;
                a.Type = CellType.Integer;
            }
            else if (SpecialSymbol.Contains(x))
            {
                a.stringData = x;
                a.Type = CellType.SpecialSymbol;
            }
            else
            {
                a.Type = CellType.Symbol;
            }

            a.car = a;
            return a;
        }

        public override string ToString()
        {
            if (Type == CellType.Nil)
            {
                return "()";
            }
            else if (Type == CellType.Integer)
            {
                return intData.ToString();
            }
            else if (Type == CellType.Pair)
            {
                string t1 = car.ToString();
                string t2 = cdr.ToString();

                return "(" + t1 + " " + t2 + ")";
            }
            else if (Type == CellType.Operater)
            {
                //
                string t2 = cdr.ToString();
                return "(" + stringData + " " + t2 + ")";
            }
            else if (Type == CellType.Symbol)
            {
                return stringData;

            }
            else if (Type == CellType.SpecialSymbol)
            {
                return stringData;
            }
            else if (Type == CellType.Syntax)
            {
                if (this == "let")
                {
                    return "(" + stringData + " " + cdr.ToString() + ")";
                }
                else
                {
                    return base.ToString();
                }
            }
            else if (Type == CellType.Lambda)
            {
                return "(" + stringData + " " + cdr.ToString() + ")";
            }
            else if (Type == CellType.Quote)
            {
                return cdr.ToString();
            }

            return base.ToString();
        }

        public static bool operator ==(Pair p1, Pair p2)
        {
            if (object.Equals(p1, null) || object.Equals(p2, null))
            {
                return false;
            }

            if (p1.Type == p2.Type)
            {
                if (p1.Type == CellType.Symbol)
                {
                    return p1.stringData == p2.stringData;
                }
                else if (p1.Type == CellType.Integer)
                {
                    return p1.intData == p2.intData;
                }
                else
                {
                    return p1.stringData == p2.stringData;
                }
            }
            else
            {
                return false;
            }
        }

        public static bool operator !=(Pair p1, Pair p2)
        {
            return !(p1 == p2);
        }

        public static bool operator >(Pair p1, Pair p2)
        {
            return (int) p1 > p2;
        }

        public static bool operator <(Pair p1, Pair p2)
        {
            return !(p1 > p2);
        }
    }