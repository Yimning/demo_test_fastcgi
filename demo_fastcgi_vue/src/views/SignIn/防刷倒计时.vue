 <!-- 考试倒计时组件 -->
<template>
 <div class="time">
  <p>00:{{timerCount2}}:{{timerCount1}}</p>
  <button @click="reset">重新计时</button>
 </div>
</template>

<script>
export default {
 name: "Time",  
 data() {
  return {
   timeSeconds: 0,
   timeMinutes: 0,
   seconds: 59, // 秒
   minutes: 1, // 分
   timer: null
  };
 },
 methods: {
  num(n) {
   return n < 10 ? "0" + n : "" + n;
  },
  // 重新计时
  reset() {
   sessionStorage.removeItem("answered");
   window.location.reload();
   localStorage.removeItem("startTime1");
   localStorage.removeItem("startTime2");
   clearInterval(this.timer);
  },
  // 清除
  clear() {
   localStorage.removeItem("startTime1");
   localStorage.removeItem("startTime2");
   sessionStorage.setItem("answered", 1);
   clearInterval(this.timer); 
  }, 
  // 倒计时     
  timing() {
   let [startTime1, startTime2] = [ localStorage.getItem("startTime1"), localStorage.getItem("startTime2") ];
   let nowTime = new Date().getTime();
   if (startTime1) {
    let surplus = this.seconds - parseInt((nowTime - startTime1) / 1000);
    this.timeSeconds = surplus <= 0 ? 0 : surplus;
   } else {
    this.timeSeconds = this.seconds;
    localStorage.setItem("startTime1", nowTime); //存储秒
   }
   if (startTime2) {
    this.timeMinutes = startTime2;
   } else {
    this.timeMinutes = this.minutes;
    localStorage.setItem("startTime2", this.minutes); //存储分
   }
   this.timer = setInterval(() => {
    if ( this.timeSeconds == 0 && this.timeMinutes != 0 && this.timeMinutes > 0 ) {
     let nowTime = new Date().getTime();
     this.timeSeconds = this.seconds;
     localStorage.setItem("startTime1", nowTime);
     this.timeMinutes--;
     localStorage.setItem("startTime2", this.timeMinutes);
    } else if (this.timeMinutes == 0 && this.timeSeconds == 0) {
     this.timeSeconds = 0;
     this.clear();
     alert("考试时间到");
    } else {
     this.timeSeconds--;
    }
   }, 1000);
  }
 },
 mounted() {
  if (sessionStorage.getItem("answered") != 1) {
   this.timing();
  }
 },
 computed: {
  timerCount1() {
   return this.timeSeconds < 10 ? "0" + this.timeSeconds : "" + this.timeSeconds;
  },
  timerCount2() {
   return this.timeMinutes < 10 ? "0" + this.timeMinutes : "" + this.timeMinutes;
  }
 },
 destroyed() {
  // 退出后清除计时器       
  if (this.timer) {     
   clearInterval(this.timer); 
  }   
 }  
};
</script> 
<style scoped>
.time {
 color: #f72a3a;
 font-weight: bold;
 font-size: 26px;
}
</style>