                               #pragma once

                            #include <iostream>
                             #include <chrono>
                            #include <iomanip>
                          #include <string_view>

                             namespace logging
                                     {
                             namespace detail
                                     {
                       inline void printTimestamp()
                                     {
               auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                   std::tm tm = *std::localtime(&now_c);
            std::cout << '[' << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
                      << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
                      << std::setw(2) << std::setfill('0') << tm.tm_sec << ']';
                                     }

                        template <typename... Args>
           void log(std::string_view level, const Args&... args)
                                     {
                             printTimestamp();
                    std::cout << " [" << level << "] ";
              ((std::cout << args << ' '), ...) << std::endl;
                                     }
                                     }

                        template <typename... Args>
                      void DEBUG(const Args&... args)
                                     {
                      detail::log("DEBUG", args...);
                                     }

                        template <typename... Args>
                      void INFO(const Args&... args)
                                     {
                       detail::log("INFO", args...);
                                     }

                        template <typename... Args>
                     void WARNING(const Args&... args)
                                     {
                     detail::log("WARNING", args...);
                                     }

                        template <typename... Args>
                      void ERROR(const Args&... args)
                                     {
                      detail::log("ERROR", args...);
                                     }

                        template <typename... Args>
                    void CRITICAL(const Args&... args)
                                     {
                     detail::log("CRITICAL", args...);
                                     }
                                     }
