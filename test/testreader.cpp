#include <gtest/gtest.h>
#include <iostream>

#include <libasync/io/reader.hpp>
#include <libasync/utils/observer.hpp>

class test_observer final : public libasync::utils::observer<std::string>,
                            public std::enable_shared_from_this<test_observer> {
  std::stringstream& output_;
  std::unique_ptr<libasync::io::ireader> reader_;

public:
  explicit test_observer(std::stringstream& out,
                         std::unique_ptr<libasync::io::ireader> reader) noexcept
    : output_(out), reader_(std::move(reader)) {}

  void update(const std::string& str) noexcept override {
    output_ << str << '\n';
  }

  void start() {
    auto this_ptr = shared_from_this();

    std::weak_ptr<test_observer> weak_ptr(this_ptr);
    reader_->attach(weak_ptr);
    reader_->read_cycle();
    reader_->detach(weak_ptr);
  }

  std::string as_str() noexcept {
    return output_.str();
  }
};

class test_reader : public ::testing::Test {
protected:
  std::unique_ptr<std::stringstream> input;
  std::unique_ptr<std::stringstream> output;
  std::unique_ptr<std::stringstream> expected;

  std::unique_ptr<libasync::io::ireader> rd;
  std::shared_ptr<test_observer> tst_obs;

  void SetUp() override {
    input = std::make_unique<std::stringstream>();
    output = std::make_unique<std::stringstream>();
    expected = std::make_unique<std::stringstream>();
    rd = std::make_unique<libasync::io::reader>(*input);
    tst_obs = std::make_shared<test_observer>(*output, std::move(rd));
  }

  void TearDown() override {
    input.reset();
    output.reset();
    expected.reset();
    rd.reset();
    tst_obs.reset();
  }
};

TEST_F(test_reader, test_reader1) {
  *input << "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n";
  *expected << "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n";

  tst_obs->start();

  //  std::cout << tst_obs->as_str() << std::endl;
  ASSERT_EQ(tst_obs->as_str(), expected->str());
}

TEST_F(test_reader, test_reader2) {
  *input << "cmd1\n"
            "cmd2\n"
            "{\n"
            "cmd3\n"
            "cmd4\n"
            "}\n"
            "cmd5\n"
            "cmd6\n";
  *expected << "cmd1\ncmd2\n{\ncmd3\ncmd4\n}\ncmd5\ncmd6\n";

  tst_obs->start();

  //  std::cout << tst_obs->as_str() << std::endl;
  ASSERT_EQ(tst_obs->as_str(), expected->str());
}
