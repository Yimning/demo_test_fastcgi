<template>
    <div>
        <el-row :gutter="20">
            <el-col :span="8">
                <el-card shadow="hover" class="mgb20" style="height: 252px">
                    <div class="user-info">
                        <img :src="userAvatar" class="user-avator" alt />
                        <div class="user-info-cont">
                            <div class="user-info-name">{{ userInfo.userName }}</div>
                            <div>{{ role }}</div>
                        </div>
                    </div>
                    <div class="user-info-list">
                        上次登录时间：
                        <span>{{ this.$store.getters.getUser.loginTime }}</span>
                    </div>
                    <div class="user-info-list">
                        上次登录地点：
                        <span>{{ this.$store.getters.getUser.loginPlace }}</span>
                    </div>
                </el-card>
                <el-card shadow="hover" style="height: 252px" v-if="isAdmin">
                    <div slot="header" class="clearfix">
                        <span>人员比例</span>
                    </div>
                    {{ '管理员' }}<el-progress :percentage="parseInt(userList.adminPercent)" color="#42b983"></el-progress> {{ '教师'
                    }}<el-progress :percentage="parseInt(userList.teacherPercent)" color="#f1e05a"></el-progress> {{ '学生'
                    }}<el-progress :percentage="parseInt(userList.studentPercent)"></el-progress>
                    <!-- HTML<el-progress :percentage="5.9" color="#f56c6c"></el-progress> -->
                </el-card>
                <el-card shadow="hover" style="height: 252px" v-else>
                    <div slot="header" class="clearfix">
                        <span>近期课程出勤率</span>
                    </div>
                    {{ recentAttendanceList.courseName
                    }}<el-progress :percentage="parseInt(recentAttendanceInfo.percent)" color="#42b983"></el-progress>
                    <!-- JavaScript<el-progress :percentage="24.1" color="#f1e05a"></el-progress>
                    CSS <el-progress :percentage="13.7"></el-progress>
                    HTML<el-progress :percentage="5.9" color="#f56c6c"></el-progress> -->
                </el-card>
            </el-col>
            <el-col :span="16" v-if="tsRose">
                <el-row :gutter="20" class="mgb20" ref="dateList" :model="recentAttendanceList" v-if="tsRose">
                    <el-col :span="8">
                        <el-card shadow="hover" :body-style="{ padding: '0px' }">
                            <div class="grid-content grid-con-1">
                                <i class="el-icon-lx-notice grid-con-icon"></i>
                                <div class="grid-cont-right">
                                    <el-button type="text" @click="courseBtn">
                                        <div class="grid-num">
                                            {{ recentAttendanceList.courseID }}
                                        </div>
                                    </el-button>
                                    <div>最近签到课程:</div>
                                    <div>{{ recentAttendanceList.courseName }}</div>
                                    <div>{{ recentAttendanceList.recordTime }}</div>
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                    <el-col :span="8" :model="recentAttendanceInfo">
                        <el-card shadow="hover" :body-style="{ padding: '0px' }">
                            <div class="grid-content grid-con-2">
                                <i class="el-icon-lx-people grid-con-icon"></i>
                                <div class="grid-cont-right">
                                    <el-button type="text" @click="allFlagBtn">
                                        <div class="grid-num">{{ recentAttendanceInfo.allFlag }}</div>
                                    </el-button>

                                    <div>应出勤人数</div>
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                    <el-col :span="8">
                        <el-card shadow="hover" :body-style="{ padding: '0px' }">
                            <div class="grid-content grid-con-3">
                                <i class="el-icon-s-custom grid-con-icon"></i>
                                <div class="grid-cont-right">
                                    <el-button type="text" @click="notFlagBtn">
                                        <div class="grid-num">{{ recentAttendanceInfo.notFlag }}</div>
                                    </el-button>
                                    <div>缺勤人数</div>
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                </el-row>
                <el-card shadow="hover" style="height: 403px" :model="recentCourseList" v-if="tsRose">
                    <div slot="header" class="clearfix">
                        <span>待上课课程</span>
                        <el-button style="float: right; padding: 3px 0" type="text" @click="courseTable">课程表</el-button>
                    </div>
                    <el-table :show-header="false" :data="recentCourseList" style="width: 100%">
                        <el-table-column width="40">
                            <template slot-scope="scope">
                                <el-checkbox v-model="scope.row.status"></el-checkbox>
                            </template>
                        </el-table-column>
                        <el-table-column>
                            <template slot-scope="scope">
                                <div class="todo-item" :class="{ 'todo-item-del': scope.row.status }">
                                    课程:{{ scope.row.courseName }}—— 地点:{{ scope.row.classRoomID }}—— 时间:{{
                                        scope.row.weekDay + '' + scope.row.courseTime
                                    }}—— 节数:{{ scope.row.coursePeriodF + '-' + scope.row.coursePeriodB }}节
                                </div>
                            </template>
                        </el-table-column>
                        <el-table-column width="60">
                            <template slot-scope="scope">
                                <el-button
                                    class="el-icon-edit"
                                    style="float: right; padding: 3px 0"
                                    type="text"
                                    @click="detail(scope.$index, scope.row)"
                                    >详情</el-button
                                >
                                <!-- <i class="el-icon-edit"></i>
                                <i class="el-icon-delete"></i> -->
                            </template>
                        </el-table-column>
                    </el-table>
                    <el-dialog title="课程信息" :visible.sync="showUsualCourseDialog" width="30%" center>
                        <div class="dialog-content">
                            <div v-if="typeof selectedCourse != 'undefined'">
                                <div>课程名称： {{ selectedCourse.courseName }}</div>
                                <div>
                                    上课时间：
                                    {{ selectedCourse.courseTime }}
                                </div>
                                <div>
                                    课程信息：
                                    {{
                                        '每周' +
                                        selectedCourse.courseDay +
                                        ' ' +
                                        '第' +
                                        selectedCourse.coursePeriodF +
                                        '-' +
                                        selectedCourse.coursePeriodB +
                                        '节'
                                    }}
                                </div>

                                <div>上课地点： {{ selectedCourse.classRoomID }}</div>
                                <div>上课教师： {{ selectedCourse.teacherName }}</div>
                                <div>上课周期： {{ selectedCourse.courseWeekF + '-' + selectedCourse.courseWeekB + '周' }}</div>
                            </div>
                            <div v-else class="tip">本学期没有课哦！</div>
                        </div>
                        <span slot="footer" class="dialog-footer">
                            <el-button type="primary" @click="showUsualCourseDialog = false">确 定</el-button>
                            <el-button v-if="isTeacher" type="primary" @click="signIn">进行签到</el-button>
                        </span>
                    </el-dialog>
                </el-card>
            </el-col>
            <el-col :span="16" v-if="isAdmin">
                <el-row :gutter="20" class="mgb20" ref="userList" :model="userList">
                    <el-col :span="8">
                        <el-card shadow="hover" :body-style="{ padding: '0px' }">
                            <div class="grid-content grid-con-1">
                                <i class="el-icon-lx-notice grid-con-icon"></i>
                                <div class="grid-cont-right">
                                    <el-button type="text" @click="adminCountBtn">
                                        <div class="grid-num">{{ userList.adminCount }}</div>
                                    </el-button>

                                    <div>管理员人数</div>
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                    <el-col :span="8" :model="userList">
                        <el-card shadow="hover" :body-style="{ padding: '0px' }">
                            <div class="grid-content grid-con-2">
                                <i class="el-icon-lx-people grid-con-icon"></i>
                                <div class="grid-cont-right">
                                    <el-button type="text" @click="teacherCountBtn">
                                        <div class="grid-num">{{ userList.teacherCount }}</div>
                                    </el-button>

                                    <div>教师人数</div>
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                    <el-col :span="8">
                        <el-card shadow="hover" :body-style="{ padding: '0px' }">
                            <div class="grid-content grid-con-3">
                                <i class="el-icon-s-custom grid-con-icon"></i>
                                <div class="grid-cont-right">
                                    <el-button type="text" @click="stuCountBtn">
                                        <div class="grid-num">{{ userList.stuCount }}</div>
                                    </el-button>
                                    <div>学生人数</div>
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                </el-row>
                <el-card shadow="hover" style="height: 403px" :model="todoList">
                    <div slot="header" class="clearfix">
                        <span>待办</span>
                        <el-button style="float: right; padding: 3px 0" type="text" @click="toDo">刷新</el-button>
                    </div>
                    <el-table :show-header="false" :data="todoList" style="width: 100%">
                        <el-table-column width="40">
                            <template slot-scope="scope">
                                <el-checkbox v-model="scope.row.status"></el-checkbox>
                            </template>
                        </el-table-column>
                        <el-table-column>
                            <template slot-scope="scope">
                                <div class="todo-item" :class="{ 'todo-item-del': scope.row.status }">
                                    {{ scope.row.title }}
                                </div>
                            </template>
                        </el-table-column>
                        <el-table-column width="60">
                            <template slot-scope="scope">
                                <el-button
                                    class="el-icon-edit"
                                    style="float: right; padding: 3px 0"
                                    type="text"
                                    @click="detail(scope.$index, scope.row)"
                                    >详情</el-button
                                >
                                <!-- <i class="el-icon-edit"></i>
                                <i class="el-icon-delete"></i> -->
                            </template>
                        </el-table-column>
                    </el-table>
                </el-card>
            </el-col>
        </el-row>
        <el-row :gutter="20">
            <el-col :span="12">
                <el-card shadow="hover" v-if="isAdmin">
                    <schart ref="bar" class="schart" canvasId="bar" :options="adminOptionBar"></schart>
                </el-card>
            </el-col>
            <el-col :span="12" v-if="isAdmin">
                <el-card shadow="hover">
                    <schart class="schart" canvasId="ring" :options="adminOptionsRing"></schart>
                </el-card>
            </el-col>
            <el-col :span="12" v-if="tsRose">
                <el-card shadow="hover">
                    <schart ref="bar" class="schart" canvasId="bar" :options="tsOptionsBar"></schart>
                </el-card>
            </el-col>
            <el-col :span="12" v-if="tsRose">
                <el-card shadow="hover">
                    <schart class="schart" canvasId="ring" :options="tsOptionsRing"></schart>
                </el-card>
            </el-col>
        </el-row>
    </div>
</template>

<script>
import Schart from 'vue-schart';
import bus from '../components/common/bus';
import { timeFix } from '../utils/util';
import { sendWebSocket, closeWebSocket } from '@/utils/websocket.js';
import StuAttendenceRecordsVue from './SignIn/StuAttendenceRecords.vue';
const weekArr = ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六'];
export default {
    name: 'dashboard',
    inject: ['reload'],
    data() {
        return {
            userInfo: this.$store.getters.getUser,
            userAvatar: this.$store.getters.getUser.avatar,
            roseID: this.$store.getters.getUser.roseID,
            roseName: this.$store.getters.getUser.roseName,
            form: {},
            tsRose: false,
            params: {},
            requestUrl: '',
            list: [],
            newArray: [],
            recentAttendanceList: [],
            recentCourseList: [],
            recentAttendanceInfo: {
                allFlag: '',
                notFlag: '',
                percent: 0
            },
            json: {
                course: {},
                student: {},
                teacher: {}
            },
            weeks: {
                0: '星期日',
                1: '星期一',
                2: '星期二',
                3: '星期三',
                4: '星期四',
                5: '星期五',
                6: '星期六'
            },
            showUsualCourseDialog: false,
            isTeacher: false,
            isAdmin: false,
            selectedCourse: [],
            userList: {
                studentPercent: 0,
                teacherPercent: 0,
                adminPercent: 0,
                stuCount: 0,
                teacherCount: 0,
                adminCount: 0,
                allUser: 0
            },
            todoList: [
                {
                    title: '今天要修复100个bug',
                    status: false
                },
                {
                    title: '今天已修复100个bug',
                    status: false
                },
                {
                    title: '今天要写100行代码加几个bug吧',
                    status: false
                }
            ],
            data: [
                {
                    name: '2018/09/04',
                    value: 1083
                },
                {
                    name: '2018/09/05',
                    value: 941
                },
                {
                    name: '2018/09/06',
                    value: 1139
                },
                {
                    name: '2018/09/07',
                    value: 816
                },
                {
                    name: '2018/09/08',
                    value: 327
                },
                {
                    name: '2018/09/09',
                    value: 228
                },
                {
                    name: '2018/09/10',
                    value: 1065
                }
            ],
            adminOptionBar: {
                type: 'bar',
                title: {
                    text: '用户人数柱形图'
                },
                xRorate: 25,
                labels: ['管理员', '教师', '学生'],

                datasets: [
                    {
                        label: '管理员',
                        data: [0]
                    },
                    {
                        label: '教师',
                        data: [, 0]
                    },
                    {
                        label: '学生',
                        data: [, , 0]
                    }
                ]
            },
            adminOptionsRing: {
                type: 'ring',
                title: {
                    text: '用户比例环形图'
                },
                showValue: false,
                legend: {
                    position: 'bottom',
                    bottom: 40
                },
                bgColor: '#fbfbfb',
                labels: ['管理员', '教师', '学生'],
                datasets: [
                    {
                        data: [0, 0, 0]
                    }
                ]
            },
            tsOptionsBar: {
                type: 'bar',
                title: {
                    text: '最近课程签到情况柱形图'
                },
                xRorate: 25,
                labels: ['应出勤', '实勤', '缺勤'],
                datasets: [
                    {
                        label: '应出勤',
                        data: [0]
                    },
                    {
                        label: '实勤',
                        data: [, 0]
                    },
                    {
                        label: '缺勤',
                        data: [, , 0]
                    }
                ]
            },
            tsOptionsRing: {
                type: 'ring',
                title: {
                    text: '用户比例环形图'
                },
                showValue: false,
                legend: {
                    position: 'bottom',
                    bottom: 40
                },
                bgColor: '#fbfbfb',
                labels: ['实勤', '缺勤'],
                datasets: [
                    {
                        data: [0, 0]
                    }
                ]
            }
        };
    },
    components: {
        Schart
    },
    beforeDestroy() {
        // 页面销毁时关闭ws。因为有可能ws连接接收数据尚未完成，用户就跳转了页面
        // 在需要主动关闭ws的地方都可以调用该方法
        closeWebSocket();
    },
    computed: {
        role() {
            return '角色:' + this.roseName;
        }
    },
    created() {
        this.handleListener();
        this.changeDate();
        this.recentCourse();
        if (this.$store.getters.getUser.roseID != '2') {
            this.tsRose = true;
        } else {
            this.isAdmin = true;
            this.userCount();
        }
        const url = '/api/attendance/findAttendanceInfo';
        //学生
        if (this.$store.getters.getUser.roseID == '0') {
            this.params = {
                params: {
                    courseID: null,
                    studentNumber: this.$store.getters.getUser.userID,
                    studentName: null,
                    teacherNumber: null,
                    teacherName: null,
                    flag: null,
                    time: null
                }
            };
            this.StuAttendenceRecords(url, this.params);
        }
        //教师
        if (this.$store.getters.getUser.roseID == '1') {
            this.isTeacher = true; //只有教师显示
            this.params = {
                params: {
                    courseID: null,
                    studentNumber: null,
                    studentName: null,
                    teacherNumber: this.$store.getters.getUser.userID,
                    teacherName: null,
                    flag: null,
                    time: null
                }
            };
            this.TeachAttendenceRecords(url, this.params);
        }
        //websocket连接
        this.closeWebSocket();
        this.requstWs();
    },
    mounted() {
        // 延迟 1 秒显示欢迎信息
        setTimeout(() => {
            this.$notify.success({
                title: '欢迎',
                message: `${timeFix()}，欢迎回来!`
            });
        }, 1000);
    },
    activated() {
        this.handleListener();
    },
    deactivated() {
        window.removeEventListener('resize', this.renderChart);
        bus.$off('collapse', this.handleBus);
    },
    methods: {
        changeDate() {
            const now = new Date().getTime();
            this.data.forEach((item, index) => {
                const date = new Date(now - (6 - index) * 86400000);
                item.name = `${date.getFullYear()}/${date.getMonth() + 1}/${date.getDate()}`;
            });
        },
        handleListener() {
            bus.$on('collapse', this.handleBus);
            // 调用renderChart方法对图表进行重新渲染
            window.addEventListener('resize', this.renderChart);
        },
        handleBus(msg) {
            setTimeout(() => {
                this.renderChart();
            }, 200);
        },
        renderChart() {
            // this.$refs.bar.renderChart();
            // this.$refs.line.renderChart();
        },
        StuAttendenceRecords(url, params) {
            const that = this;
            const url1 = '/api/scourse/findScourseByteacherNumbercIDcD';
            const url2 = '/api/attendance/findAttendanceInfo';
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', res);
                    if (res.data.length != 0) {
                        this.json = res.data[0];
                        //console.log('this.json数据结果', this.json);
                        this.newArray = this.dataTraversal(this.form);
                        this.recentAttendanceList = this.newArray[0];
                        const params1 = {
                            params: {
                                tID: this.json.teacher.teacherNumber,
                                cID: this.json.courseID,
                                cD: null
                            }
                        };
                        const params2 = {
                            params: {
                                courseID: this.json.courseID,
                                studentNumber: null,
                                studentName: null,
                                teacherNumber: this.json.teacher.teacherNumber,
                                teacherName: null,
                                flag: 0,
                                time: this.json.recordTime
                            }
                        };
                        this.recentAttendanceFlag(url1, params1, url2, params2);
                    }
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        TeachAttendenceRecords(url, params) {
            const that = this;
            const url1 = '/api/scourse/findScourseByteacherNumbercIDcD';
            const url2 = '/api/attendance/findAttendanceInfo';
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', res);
                    if (res.data.length != 0) {
                        this.json = res.data[0];
                        //console.log('this.json数据结果', this.json);
                        this.newArray = this.dataTraversal(this.form);
                        this.recentAttendanceList = this.newArray[0];
                        const params1 = {
                            params: {
                                tID: this.json.teacher.teacherNumber,
                                cID: this.json.courseID,
                                cD: null
                            }
                        };
                        const params2 = {
                            params: {
                                courseID: this.json.courseID,
                                studentNumber: null,
                                studentName: null,
                                teacherNumber: this.$store.getters.getUser.userID,
                                teacherName: null,
                                flag: 0,
                                time: this.json.recordTime
                            }
                        };
                        this.recentAttendanceFlag(url1, params1, url2, params2);
                    }
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        recentAttendanceFlag(url1, params1, url2, params2) {
            const that = this;
            var r0 = this.$axios.get(url1, params1);
            var r1 = this.$axios.get(url2, params2);
            //并发请求
            this.$axios
                .all([r0, r1])
                .then(
                    that.$axios.spread((res1, res2) => {
                        console.log(res1, res2);
                        this.recentAttendanceInfo.allFlag = res1.data.length;
                        this.recentAttendanceInfo.notFlag = res2.data.length;
                        let number =
                            (this.recentAttendanceInfo.allFlag - this.recentAttendanceInfo.notFlag) / this.recentAttendanceInfo.allFlag;
                        this.recentAttendanceInfo.percent = Number(number * 100).toFixed(0);
                        this.tsOptionsBar.datasets[0].data = [this.recentAttendanceInfo.allFlag];
                        this.tsOptionsBar.datasets[1].data = [, this.recentAttendanceInfo.allFlag - this.recentAttendanceInfo.notFlag];
                        this.tsOptionsBar.datasets[2].data = [, , this.recentAttendanceInfo.notFlag];
                        this.tsOptionsRing.datasets[0].data = [
                            this.recentAttendanceInfo.allFlag - this.recentAttendanceInfo.notFlag,
                            this.recentAttendanceInfo.notFlag
                        ];
                    })
                )
                .catch((err) => {
                    console.log(err);
                });
        },
        courseTable() {
            this.$router.push({ path: '/Courses' });
        },
        toDo() {
             this.reload(); //刷新 ----推荐
        },
        detail(e, data) {
            //console.log(e, data);
            this.selectedCourse = data;
            this.showUsualCourseDialog = true;
        },
        signIn() {
            //获取当前的课程信息
            // console.log(this.selectedCourse);

            //将数组转成对象
            var obj = {};
            for (var i in this.selectedCourse) {
                obj[i] = this.selectedCourse[i];
            }
            this.dataParams = obj;
            var aData = new Date();
            //console.log( this.dataDateNumber(aData));//显示当前星期几
            if (this.selectedCourse.courseID == this.dataDateNumber(aData)) {
                sessionStorage.setItem('dataParams', JSON.stringify(this.dataParams));
                this.showUsualCourseDialog = false;
                this.$router.push({ path: '/SignIn', query: { data: this.dataParams } }); //路由跳转传参
            } else {
                this.$confirm('当前课程时间不一致, 是否进行签到?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                })
                    .then(() => {
                        sessionStorage.setItem('dataParams', JSON.stringify(this.dataParams));
                        this.showUsualCourseDialog = false;
                        this.$router.push({ path: '/SignIn', query: { data: this.dataParams } }); //路由跳转传参
                    })
                    .catch(() => {
                        this.$message({
                            type: 'info',
                            message: '已取消'
                        });
                        this.showUsualCourseDialog = false;
                    });
            }
        },
        recentCourse() {
            const that = this;
            var aData = new Date();
            // this.dataDateNumber(aData);//星期几的索引
            if (this.$store.getters.getUser.roseID == '1') {
                const params = { params: { tID: this.$store.getters.getUser.userID, cID: null, cD: this.dataDateNumber(aData) } };
                const that = this;
                //axios的get请求
                this.$axios
                    .get('/api/scourse/findScourseBytIDcIDcD', params)
                    .then((res) => {
                        //console.log('请求后台数据结果', res);
                        this.form = res.data;
                        this.newArray = this.dataTraversal(this.form);
                        this.recentCourseList = this.newArray;
                        //console.log(this.recentCourseList);
                    })
                    .catch((err) => {
                        console.log(err);
                    });
            }
            if (this.$store.getters.getUser.roseID == '0') {
                const params = { params: { sID: this.$store.getters.getUser.userID, cID: null, cD: this.dataDateNumber(aData) } };
                const that = this;
                //axios的get请求
                this.$axios
                    .get('/api/scourse/findScourseBysIDcIDcD', params)
                    .then((res) => {
                        this.form = res.data;
                        this.newArray = this.dataTraversal(this.form);
                        this.recentCourseList = this.newArray;
                    })
                    .catch((err) => {
                        console.log(err);
                    });
            }
        },
        userCount() {
            const that = this;
            var r0 = this.$axios.get('/api/student/count');
            var r1 = this.$axios.get('/api/teacher/count');
            var r2 = this.$axios.get('/api/admin/count');
            //并发请求
            this.$axios
                .all([r0, r1, r2])
                .then(
                    that.$axios.spread((res0, res1, res2) => {
                        //console.log(res0, res1, res2);
                        this.userList.stuCount = res0.data;
                        this.userList.teacherCount = res1.data;
                        this.userList.adminCount = res2.data;
                        this.allUser = this.userList.stuCount + this.userList.teacherCount + this.userList.adminCount;
                        this.userList.studentPercent = Number((this.userList.stuCount / this.allUser) * 100).toFixed(0);
                        this.userList.teacherPercent = Number((this.userList.teacherCount / this.allUser) * 100).toFixed(0);
                        this.userList.adminPercent = Number((this.userList.adminCount / this.allUser) * 100).toFixed(0);
                        this.adminOptionBar.datasets[0].data = [this.userList.adminCount];
                        this.adminOptionBar.datasets[1].data = [, this.userList.teacherCount];
                        this.adminOptionBar.datasets[2].data = [, , this.userList.stuCount];
                        this.adminOptionsRing.datasets[0].data = [
                            this.userList.adminCount,
                            this.userList.teacherCount,
                            this.userList.stuCount
                        ];
                    })
                )
                .catch((err) => {
                    console.log(err);
                });
        },
        courseBtn() {
            this.allFlagBtn();
        },
        allFlagBtn() {
            if (this.$store.getters.getUser.roseID == '0') {
                this.$router.push({ path: '/recentAttendence' });
            }
            if (this.$store.getters.getUser.roseID == '1') {
                this.$router.push({ path: '/recentAttendence' });
            }
        },
        notFlagBtn() {
            this.allFlagBtn();
        },
        stuCountBtn() {
            this.$router.push({ path: '/students' });
        },
        teacherCountBtn() {
            this.$router.push({ path: '/teachers' });
        },
        adminCountBtn() {
            this.$message.error('无权限查看');
        },

        dataTraversal(form) {
            this.list = [];
            this.newArray = [];
            for (const i in form) {
                //console.log('属性:' + i);
                this.$set(this.list, 'recordID', form[i].recordID);
                this.$set(this.list, 'recordTime', form[i].recordTime);
                this.$set(this.list, 'flag', form[i].flag);
                this.$set(this.list, 'weekDay', this.dataDateChange(form[i].recordTime));

                for (const key in form[i].course) {
                    this.$set(this.list, key, form[i].course[key]); //对象新增属性(使用Vue.$set())
                    if (key == 'courseDay') {
                        this.$set(this.list, 'weekDay', this.weeks[form[i].course[key]]);
                    }
                    this.newArray[i] = this.list; //新建数组存放
                }
                for (const key in form[i].student) {
                    //console.log("属性:"+key);
                    this.$set(this.list, key, form[i].student[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                for (const key in form[i].teacher) {
                    //console.log("属性:"+key);
                    this.$set(this.list, key, form[i].teacher[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                this.list = []; //循环完必须清空,否则可能会覆盖
            }
            return this.newArray;
        },
        // 时间格式化
        dataFormat(value) {
            if (value != null || value == '') {
                var year = value.substr(0, 4);
                var month = value.substr(5, 2);
                var day = value.substr(8, 2);
                var hour = value.substr(11, 2);
                var min = value.substr(14, 2);
                var second = value.substr(17, 2);
                return year + '-' + month + '-' + day + ' ' + hour + ':' + min + ':' + second;
            } else return null;
        },
        //根据当前的日期显示当前是星期几
        dataDateChange(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                //this.week = this.weeks[weekIndex];
                return this.weeks[weekIndex];
            } else return null;
        },
        //根据当前的日期显示当前是星期几的索引
        dataDateNumber(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                return weekIndex;
            } else return null;
        },
        GMTToStr: function (time) {
            let date = new Date(time);
            let Str =
                date.getFullYear() +
                '-' +
                (date.getMonth() + 1) +
                '-' +
                date.getDate() +
                ' ' +
                date.getHours() +
                ':' +
                date.getMinutes() +
                ':' +
                date.getSeconds();
            return Str;
        },
        StrToGMT(time) {
            let GMT = new Date(time);
            return GMT;
        },

        // ws连接成功，后台返回的ws数据，组件要拿数据渲染页面等操作
        wsMessage(data) {
            const dataJson = JSON.stringify({ data });
            console.log('dataJson:' + dataJson);
            // 这里写拿到数据后的业务代码
        },
        // ws连接失败，组件要执行的代码
        wsError() {
            // 比如取消页面的loading
        },
        requstWs() {
            // 防止用户多次连续点击发起请求，所以要先关闭上次的ws请求。
            closeWebSocket();
            // 跟后端协商，需要什么参数数据给后台
            const obj = {
                monitorUrl: '',
                userName: ''
            };
            // 发起ws请求
            // const baseUrl = 'ws://localhost:8082/websocket/';
            // 协议标识符是ws（如果加密，则为wss），服务器网址就是 URL。 跟http与https一样
            const baseUrl = 'wss://www.yimning.cn:8082/websocket/';
            sendWebSocket(baseUrl + this.$store.getters.getUser.userID, '', this.wsMessage, this.wsError);
            let url = '/api/webSocket/serialPorts?shopId=' + this.$store.getters.getUser.userID;

            // 这里只是一个基于axios的ajax请求，你可以换成你的请求格式
            // this.$ajax.get(url)

            // 不想安装axios了，这里使用最原始的 js去请求
            // var xhr = new XMLHttpRequest () ;
            // xhr.open('get',url,true);
            // xhr.send("fff");
        },
        closeWebSocket() {
            closeWebSocket();
        }
    }
};
</script>


<style scoped>
.el-row {
    margin-bottom: 20px;
}

.grid-content {
    display: flex;
    align-items: center;
    height: 100px;
}

.grid-cont-right {
    flex: 1;
    text-align: center;
    font-size: 14px;
    color: #999;
}

.grid-num {
    font-size: 30px;
    font-weight: bold;
}

.grid-con-icon {
    font-size: 50px;
    width: 100px;
    height: 100px;
    text-align: center;
    line-height: 100px;
    color: #fff;
}

.grid-con-1 .grid-con-icon {
    background: rgb(45, 140, 240);
}

.grid-con-1 .grid-num {
    color: rgb(45, 140, 240);
}

.grid-con-2 .grid-con-icon {
    background: rgb(100, 213, 114);
}

.grid-con-2 .grid-num {
    color: rgb(45, 140, 240);
}

.grid-con-3 .grid-con-icon {
    background: rgb(242, 94, 67);
}

.grid-con-3 .grid-num {
    color: rgb(242, 94, 67);
}

.user-info {
    display: flex;
    align-items: center;
    padding-bottom: 20px;
    border-bottom: 2px solid #ccc;
    margin-bottom: 20px;
}

.user-avator {
    width: 120px;
    height: 120px;
    border-radius: 50%;
}

.user-info-cont {
    padding-left: 50px;
    flex: 1;
    font-size: 14px;
    color: #999;
}

.user-info-cont div:first-child {
    font-size: 30px;
    color: #222;
}

.user-info-list {
    font-size: 14px;
    color: #999;
    line-height: 25px;
}

.user-info-list span {
    margin-left: 70px;
}

.mgb20 {
    margin-bottom: 20px;
}

.todo-item {
    font-size: 14px;
}

.todo-item-del {
    text-decoration: line-through;
    color: #999;
}

.schart {
    width: 100%;
    height: 300px;
}
</style>
