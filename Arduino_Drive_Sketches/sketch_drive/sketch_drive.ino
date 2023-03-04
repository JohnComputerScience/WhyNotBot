// Define constants for the encoder pins and PWM pins
const int ENCODER_RIGHT_A = 2;
const int ENCODER_RIGHT_B = 3;
const int ENCODER_LEFT_A = 4;
const int ENCODER_LEFT_B = 5;
const int PWM_LEFT = 10;
const int PWM_RIGHT = 11;

// Define variables to hold encoder counts and previous counts
volatile long encoder_left_count = 0;
volatile long encoder_right_count = 0;
// Overall current rotation 0.0-1.0
float current_rotation = 0.0;

// Define constants for PID loop tuning
const float KP = 1.0;
const float KI = 0.0;
const float KD = 0.0;

// Define variables for PID loop
float total_rotations_left = 0;
float total_rotations_right = 0;
const float ticks_per_rotation = 48 * 74.83; // 48 TICKS per rotation of the motor and 75 rotations of the motor per rotation of the wheel as the gearbox is 75:1

// Desired wheel velocity (1800 ticks per second, 2 sec per rotation)
const float left_set_point = 1.0;
const float right_set_point = 1.0;

float process_var_left = 0.0;
float process_var_right = 0.0;

float left_proportion = 0.0;
float right_proportion = 0.0;
float left_integral = 0.0;
float right_integral = 0.0;
float left_derivative = 0.0;
float right_derivative = 0.0;
float left_error = 0.0;
float right_error = 0.0;
float left_prev_error = 0.0;
float right_prev_error = 0.0;

// Interrupt service routine for the left encoder
void encoder_left_isr()
{
  if (encoder_left_count >= ticks_per_rotation) {
    encoder_left_count -= ticks_per_rotation;
    total_rotations_left += 1;
  }
 
  if (digitalRead(ENCODER_LEFT_A) == digitalRead(ENCODER_LEFT_B)) {
    encoder_left_count++;
  } else {
    encoder_left_count--;
  }
}

// Interrupt service routine for the right encoder
void encoder_right_isr_a()
{
  // when a is rising and b is low we are going forwards
  if (digitalRead(ENCODER_RIGHT_B) == LOW) {
    encoder_right_count += 1;
  } else {
    encoder_right_count -= 1;
  }
  
  if (encoder_right_count >= ticks_per_rotation) {
    encoder_right_count -= ticks_per_rotation;
    total_rotations_right += 1;
  }
  if (encoder_right_count <= -1) {
    encoder_right_count = ticks_per_rotation - 1;
    total_rotations_right -= 1;
  }
}

void encoder_right_isr_b()
{
  // when b is rising and a is high we are going forwards
  if (digitalRead(ENCODER_RIGHT_A) == HIGH) {
    encoder_right_count += 1;
  } else {
    encoder_right_count -= 1;
  }
  
  if (encoder_right_count >= ticks_per_rotation) {
    encoder_right_count -= ticks_per_rotation;
    total_rotations_right += 1;
  }
  if (encoder_right_count <= -1) {
    encoder_right_count = ticks_per_rotation;
    total_rotations_right -= 1;
  }
}

void setup()
{
  // Set up encoder pins as inputs
  pinMode(ENCODER_LEFT_A, INPUT_PULLUP);
  pinMode(ENCODER_LEFT_B, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT_A, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT_B, INPUT_PULLUP);

  // Enable pullup resistors on encoder pins
//  digitalWrite(ENCODER_LEFT_A, HIGH);
//  digitalWrite(ENCODER_LEFT_B, HIGH);
//  digitalWrite(ENCODER_RIGHT_A, HIGH);
//  digitalWrite(ENCODER_RIGHT_B, HIGH);

  // Attach interrupt service routines to encoder pins
//  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), encoder_left_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), encoder_right_isr_a, RISING);
//  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_B), encoder_left_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_B), encoder_right_isr_b, RISING);


  // Set up PWM pins as outputs
  pinMode(PWM_LEFT, OUTPUT);
  pinMode(PWM_RIGHT, OUTPUT);
  analogWrite(PWM_RIGHT, 255);

  Serial.begin(9600);
}

void loop()
{ 
  // Calculate left and right velocities based on encoder counts
  current_rotation = (encoder_right_count / ticks_per_rotation);
  
  Serial.println("data:");
  Serial.println(String(total_rotations_right) + " total rotations");
  Serial.println(String(current_rotation) + " Current rotation");
  delay(1000);

//  encoder_left_prev = encoder_left_count;
//  encoder_right_prev = encoder_right_count;
//
//  // Calculate left and right PID errors
//  left_proportion = (left_set_point - process_var_left) * KP;
//  right_proportion = (right_set_point - process_var_right) * KP;
//
//  // Calculate left and right PID terms
//  left_integral += left_proportion * KI;
//  right_integral += right_proportion * KI;
//  
//  left_derivative = (left_proportion - left_prev_error) * KD;
//  right_derivative = (right_proportion - right_prev_error) * KD;
//  
//  left_prev_error = left_proportion;
//  right_prev_error = right_proportion;
//  left_error = left_proportion + left_integral + left_derivative;
//  right_error = right_proportion + right_integral + right_derivative;
//  if (left_error > 255) { left_error = 255; }
//  if (right_error > 255) { right_error = 255; }

//  Serial.println(left_error);
//  Serial.println(right_error);
//  
  // Set PWM values based on PID outputs
//  analogWrite(PWM_LEFT, (int)left_error);
//  analogWrite(PWM_RIGHT, (int)right_error);
}

// I'm going to bed...
