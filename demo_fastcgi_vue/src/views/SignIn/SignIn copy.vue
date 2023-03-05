<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-redpacket_fill"></i> 课程考勤 </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <!-- <div class="getface">
                <img id="imgTag" src alt="imgTag" style="display: none;" />
            </div>-->
            <el-button type="primary" icon="el-icon-camera-solid" @click="openCamera">打开摄像头</el-button>
            <el-button type="primary" icon="el-icon-camera-solid" @click="closeCamera">关闭摄像头</el-button>
             <el-button type="primary" icon="el-icon-camera-solid" @click="countDown">倒计时</el-button>
            <div class="time">
                <p>00:{{minute}}:{{second}}</p>
                <!-- <button @click="reset">重新计时</button> -->
            </div>
            <!--提示-->
            <div align="center">
                <p id="flag" class="tishi"></p>
            </div>

            <div align="center">
                <!--开启摄像头-->
                <video id="video" ref="video" width="480px" height="400px" autoplay="autoplay"></video>
                <!-- <video id="video" preload autoplay loop muted></video> -->
                <!--canvas截取流-->
                <canvas ref="canvas" id="canvas" width="480px" height="400px" style="display: none"></canvas>
            </div>
        </div> 
    </div>
</template> 
  
<script>
require('tracking/build/tracking-min.js');
require('tracking/build/data/face-min.js');
require('tracking/build/data/mouth-min.js');
require('tracking/examples/assets/stats.min.js');

export default {
    name: 'componentName',
    data() {
        return {
            videoEle: null,
            trackerTask: null,
            first: null,
            faceInfo: {
                imgpath: '',
                courseID: '',
                UserID: ''
            },
            dataParams: {},
            params: {},
            timeSeconds: 0,
            timeMinutes: 0,
            seconds: 59, // 秒
            minutes: 1, // 分
            timer: null
        };
    },
    created() {
        this.dataParams = this.$route.query.data;
        this.faceInfo.courseID = this.dataParams.courseID;
        console.log(this.faceInfo);
    },
    mounted() {
        if (sessionStorage.getItem('answered') != 1) {
            this.timing();
        }
    },
    computed: {
        timerCount1() {
            return this.timeSeconds < 10 ? '0' + this.timeSeconds : '' + this.timeSeconds;
        },
        timerCount2() {
            return this.timeMinutes < 10 ? '0' + this.timeMinutes : '' + this.timeMinutes;
        }
    },
    destroyed() {
        // 退出后清除计时器
        if (this.timer) {
            clearInterval(this.timer);
        }
    },
    methods: {
        created() {
            setTimeout(() => {
                this.openCamera(); // 此为绘画canvas的方法调用
            }, 2);
        },
        mounted() {},
        openCamera() {
            var video = document.getElementById('video');
            var canvas = document.getElementById('canvas');
            var context = this.$refs['canvas'].getContext('2d');
            var tracker = new tracking.ObjectTracker('face'); // 引入第三方库  cnpm install tracking --save
            tracker.setInitialScale(1);
            tracker.setStepSize(2);
            tracker.setEdgesDensity(0.1);

            this.trackerTask = tracking.track('#video', tracker, { camera: true });
            //-------  指定 canvas 的宽高 ，auto 自动播放
            let constraints = {
                video: { width: 500, height: 500 },
                audio: true
            };

            let promise = navigator.mediaDevices.getUserMedia(constraints); // h5 新的API

            promise
                .then(function (MediaStream) {
                    video.srcObject = MediaStream;
                    video.play();
                })
                .catch(function (PermissionDeniedError) {
                    console.log(PermissionDeniedError);
                });
            //--------------
            let that = this;
            that.tracker_fun(tracker, video, context, canvas); //open 摄像头，执行tracker_fun( 传入参数 )
        },
        tracker_fun(tracker, video, context, canvas) {
            let that = this;
            let set_clear;
            let flag = true;
            set_clear = setTimeout(function () {
                // 每秒 检测人脸 结果
                tracker.on('track', function (event) {
                    that.tips = '正在刷脸中';
                    // 视频流
                    context.clearRect(0, 0, canvas.width, canvas.height);
                    event.data.forEach(function (rect) {
                        context.strokeStyle = '#ff0000';
                        context.strokeRect(rect.x, rect.y, rect.width, rect.height);
                    });
                    if (event.data.length) {
                        // 会不停的去检测人脸，所以这里需要做个锁
                        if (flag) {
                            // 裁剪出人脸并绘制下来
                            const canvasUpload = document.getElementById('canvas');
                            const contextUpload = canvasUpload.getContext('2d');
                            contextUpload.drawImage(video, 0, 0, 480, 400);
                            flag = false;
                            // 人脸的basa64
                            that.faceInfo.imgpath = canvasUpload.toDataURL('image/jpeg');
                            // console.log(that.face);

                            // ajax请求
                            that.$axios
                                .post('/api/attendance/faceAttendance', JSON.stringify(that.faceInfo), {
                                    headers: {
                                        'Content-Type': 'application/json; charset=UTF-8'
                                    }
                                })
                                .then((res) => {
                                    console.log(res);
                                    // const jwt = res.headers['authorization'];
                                    // const userInfo = res.data;

                                    // // 把数据共享出去，存于this.store下
                                    // that.$store.commit('SET_TOKEN', jwt);
                                    // that.$store.commit('SET_USERINFO', userInfo);
                                    //console.log(userInfo)
                                    if (res.data.error_code === 0 && res.data.face_liveness > 0.8) {
                                        that.closeCamera();
                                        // 登录成功跳转到首页
                                        // that.$router.push('/dashboard');
                                        that.$message.success('登录成功');
                                        that.FaceLoginVisible = false;
                                    } else {
                                        // 登录失败重新进行人脸检测
                                        // continue;
                                        //that.$message.fail('记录风险');
                                    }
                                })
                                .catch((err) => {
                                    console.log(err);
                                });
                            setTimeout(() => {
                                //设置延迟执行
                                video.load();
                                that.first = null;
                                that.tracker_fun(tracker, video, context, canvas);
                            }, 2000);
                        }
                    } else {
                        that.tips = '没有检测到人脸';
                    }
                });
                clearTimeout(set_clear);
                this.tips = '重新加载摄像头';
            }, 3000);
        },
        // 关闭摄像头
        closeCamera() {
            if (!this.$refs['video'].srcObject) return;
            let stream = this.$refs['video'].srcObject;
            let tracks = stream.getTracks();
            tracks.forEach((track) => {
                track.stop();
            });
            this.$refs['video'].srcObject = null;
            this.clear();
        },
        num(n) {
            return n < 10 ? '0' + n : '' + n;
        },
        countDown(){
            this.reset();
        },
        // 重新计时
        reset() {
            sessionStorage.removeItem('answered');
            //window.location.reload();
            localStorage.removeItem('startTime1');
            localStorage.removeItem('startTime2');
            clearInterval(this.timer);
        },
        // 清除
        clear() {
            localStorage.removeItem('startTime1');
            localStorage.removeItem('startTime2');
            sessionStorage.setItem('answered', 1);
            clearInterval(this.timer);
        },
        // 倒计时
        timing() {
            let [startTime1, startTime2] = [localStorage.getItem('startTime1'), localStorage.getItem('startTime2')];
            let nowTime = new Date().getTime();
            if (startTime1) {
                let surplus = this.seconds - parseInt((nowTime - startTime1) / 1000);
                this.timeSeconds = surplus <= 0 ? 0 : surplus;
            } else {
                this.timeSeconds = this.seconds;
                localStorage.setItem('startTime1', nowTime); //存储秒
            }
            if (startTime2) {
                this.timeMinutes = startTime2;
            } else {
                this.timeMinutes = this.minutes;
                localStorage.setItem('startTime2', this.minutes); //存储分
            }
            this.timer = setInterval(() => {
                if (this.timeSeconds == 0 && this.timeMinutes != 0 && this.timeMinutes > 0) {
                    let nowTime = new Date().getTime();
                    this.timeSeconds = this.seconds;
                    localStorage.setItem('startTime1', nowTime);
                    this.timeMinutes--;
                    localStorage.setItem('startTime2', this.timeMinutes);
                } else if (this.timeMinutes == 0 && this.timeSeconds == 0) {
                    this.timeSeconds = 0;
                    this.clear();
                    this.closeCamera();
                    //alert('时间到');
                    this.checkNoFlag();
                } else {
                    this.timeSeconds--;
                }
            }, 1000);
        },
        //查询在考勤结束之后搜索未考勤的学生并把信息加入数据库
        checkNoFlag() {
            const url = '/api/scourse/findScourseByteacherNumbercIDcD';
            this.params = {
                params: {
                    cID: this.faceInfo.courseID,
                    studentNumber: null,
                    studentName: null,
                    tID: this.$store.getters.getUser.userID,
                    teacherName: null,
                    flag: null,
                    time: null
                }
            };
            this.requestHandle(url, this.params);
        },
        requestHandle(url, params) {
            const that = this;
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    console.log(res);
                    // this.form = res.data;
                    // this.dataTraversal(this.form);
                })
                .catch((err) => {
                    console.log(err);
                });
        }
    }

};
</script>

<style>
.getface {
    position: absolute;
    top: 20%;
    left: 35%;
    box-shadow: 0 0px 12px 0 rgba(0, 0, 0, 0.1);
}
.tishi {
    font-size: 20px;
}
.time {
    position: absolute;
    margin-left: 900px;
    margin-top: -25px;
    color: #f72a3a;
    font-weight: bold;
    font-size: 26px;
}
</style>