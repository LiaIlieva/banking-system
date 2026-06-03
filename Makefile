all: $(TARGET)

$(TARGET): $(OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@echo 🔗 Linking: $@
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	@echo ✅ Compilation complete! Run with: .\bin\banking_system.exe

# Изрично компилиране на всеки файл, за да няма конфликти в MinGW
$(OBJ_DIR)\main.o: src\main.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@echo 🛠️  Compiling: $<
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\Account.o: src\model\Account.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\BankEmployee.o: src\model\BankEmployee.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\CheckingAccount.o: src\model\CheckingAccount.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\Customer.o: src\model\Customer.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\DepositTransaction.o: src\model\DepositTransaction.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\Person.o: src\model\Person.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\SavingsAccount.o: src\model\SavingsAccount.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\Transaction.o: src\model\Transaction.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\TransferTransaction.o: src\model\TransferTransaction.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\WithdrawalTransaction.o: src\model\WithdrawalTransaction.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\InterestCalculator.o: src\service\InterestCalculator.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)\Statement.o: src\service\Statement.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo 🧹 Cleaning project...
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
	@echo ✨ Cleaned!

.PHONY: all clean